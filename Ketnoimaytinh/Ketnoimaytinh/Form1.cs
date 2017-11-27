using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//
using System.Threading;
//Serial
using System.IO;
using System.IO.Ports;
using System.Xml;

namespace Ketnoimaytinh
{
    public partial class Form1 : System.Windows.Forms.Form
    {
        public static string bien="";
        public static string bien1="";
        string InputData = String.Empty; // Khai báo string buff dùng cho hiển thị dữ liệu sau này.
        string ReadData = String.Empty;
        string Name1;
        string Address;
        string Phone;
        string DogName;
        string Breed;
        string DogColor;
        string ChoiseSex;
        string ChoiseDay;
        string ChoiseMonth;
        string ChoiseYear;
        string printhWeight;
        string VacDay;
        string VacMonth;
        string VacYear;
        string VAK;
        string Vactt;
        string VacName;
        string VacDoc;
        string DayT;
        string MonthT;
        string YearT;
        string dew;
        string dewname;
        string Note;
        string UID;
        Image ima;
        //String[] Ser;
        //string Ser1;
        Boolean Doc = false;
        //string COM;
        delegate void SetTextCallback(string text); // Khai bao delegate SetTextCallBack voi tham so string
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            serialPort1.Close();//Đóng cổng Serial sau khi button 4 được nhấn
        }
        public Form1()
        {
            InitializeComponent();
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(DataReceive);
            
            string[] Vaccine = { "Rabisin", "Recombitech CV9", "Biocan DHPPi", "Eurican" };
            comboBoxVaccine.Items.AddRange(Vaccine);

            string[] Deworming = { "Lopatol", "Thenium Closylate", "Espisprantel", "Dichlovos", "Praziquantel", "Milbemycin Oxime",
                                 "Ivermectin", "Pyrantel Pamoate", "Febendazole", "Piperazine", "Mebendazole"};
            comboBoxdeworming.Items.AddRange(Deworming);
            string[] Day = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };
            comboBoxDay.Items.AddRange(Day);
            string[] Month = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
            comboBoxMonth.Items.AddRange(Month);
            string[] Year = { "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019", "2020" };
            comboBoxYear.Items.AddRange(Year);
            radioButton1.Checked = false;
            radioButton2.Checked = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBoxCOM.DataSource = SerialPort.GetPortNames();// Quét các cổng COM đang hoạt động lên comboBox1           
            string[] ports = SerialPort.GetPortNames();
            //connect();
        }
        
        private void button1_Click(object sender, EventArgs e) //Kết Nối
        {
            if (!serialPort1.IsOpen) // Nếu đối tượng serialPort1 chưa được mở , sau khi nhấn button 1 thỳ…
            {
                if (comboBoxCOM.Text != "")
                {
                    serialPort1.PortName = comboBoxCOM.Text;//cổng serialPort1 = ComboBox mà bạn đang chọn
                    serialPort1.Open();// Mở cổng serialPort1
                }
                else
                {
                    MessageBox.Show("Bạn chưa kết nối thiết bị đọc với máy tính. Hãy hết nối thiết bị trước khi nhấn nút \"OK\" để phần mềm kiểm tra lại kết nối của bạn.", "Thông báo");
                    comboBoxCOM.DataSource = SerialPort.GetPortNames();
                }
                
                
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                labTTD.Text = ("Chưa kết nối.");
                labTTD.ForeColor = Color.Red;
                pictureBox1.Image = new Bitmap(Application.StartupPath + "\\Resources\\dog.png");
                //connect();
                //Nếu Timer được làm mới, Cổng serialPort1 chưa được mở thì thay đổi Text trong button1, label3…đổi màu text label3 thành màu đỏ 
            }
            else if (serialPort1.IsOpen)
            {
                labTTD.Text = ("Đã kết nối.");
                labTTD.ForeColor = Color.Green;
                pictureBox1.Image = new Bitmap(Application.StartupPath + "\\Resources\\dog-2.png");
                //Nếu Timer được làm mới, Cổng serialPort1 đã mở thì thay đổi Text trong button1, label3…đổi màu text label3 thành màu xanh
            }
            
        }

        private void button2_Click(object sender, EventArgs e) //Ngắt Kết Nối
        {
            serialPort1.Close();//Đóng cổng Serial sau khi button 4 được nhấn
        }


       
        private void button4_Click(object sender, EventArgs e)// Đọc dữ liệu
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("3");// gửi tín hiệu cho arduino biết để bắt đầu gửi tín hiệu đọc thẻ lên máy
                ReadData = "";
                Name = "";
                Address = "";
                Phone = "";
                DogName = "";
                Breed = "";
                DogColor = "";
                txtNote.Text = "";
                txtVAK.Text = "";
                txtName.Text = "";
                txtAddress.Text = "";
                txtPhone.Text = "";
                txtDogName.Text = "";
                txtBreed.Text = "";
                txtColor.Text = "";
                txtWeight.Text = "";

                txtDay.Text = "";
                txtMonth.Text = "";
                txtYear.Text = "";
                txtDayT.Text = "";
                txtMonthT.Text = "";
                txtYearT.Text = "";

                radioButton2.Checked = false;
                radioButton1.Checked = false;
                comboBoxYear.Text = "";
                comboBoxMonth.Text = "";
                comboBoxDay.Text = "";
                comboBoxVaccine.Text = "";
                txtDoctor.Text = "";
                comboBoxdeworming.Text = "";
                UID = "";
                //txtColor.Text = "";
                timer2.Enabled = true;
                Doc = true;
            }
            else if (!serialPort1.IsOpen)
            {
                MessageBox.Show("Chưa kết nối thiết bị với máy tính.", "Thông báo");
            }
            
        }
        private void timer2_Tick(object sender, EventArgs e)
        {

            String Read = ReadData;
            int DodaiRead = Read.Length;
            //MessageBox.Show(DodaiRead.ToString());
            if (DodaiRead==765)
            {
                Name1 = ReadData.Substring(0, 32).Trim();
                Address = ReadData.Substring(32, 96).Trim();
                Phone = ReadData.Substring(128, 16).Trim();
                DogName = ReadData.Substring(144, 32).Trim();
                Breed = ReadData.Substring(176, 48).Trim();
                DogColor = ReadData.Substring(224, 32).Trim();
                int Socan = int.Parse(ReadData.Substring(256, 3));
                printhWeight = Socan.ToString() + "." + ReadData.Substring(259, 1);
                ChoiseSex = ReadData.Substring(260, 1);
                ChoiseDay = ReadData.Substring(261, 2);
                ChoiseMonth = ReadData.Substring(263, 2);
                ChoiseYear = ReadData.Substring(265, 4);
                VAK = ReadData.Substring(272, 16).Trim();
                VacDay = ReadData.Substring(288, 2);
                VacMonth = ReadData.Substring(290, 2);
                VacYear = ReadData.Substring(292, 4);
                Vactt = ReadData.Substring(296, 1);
                if (Vactt == "0")
                {
                    labVac.Text = "Chưa tiêm.";
                }
                else
                {
                    if (Vactt == "1")
                    {
                        labVac.Text = "Đã tiêm.";
                    }
                    else
                    {
                        labVac.Text = "";
                    }
                }

                VacName = ReadData.Substring(304, 32).Trim();
                VacDoc = ReadData.Substring(336, 32).Trim();
                DayT = ReadData.Substring(368, 2);
                MonthT = ReadData.Substring(370, 2);
                YearT = ReadData.Substring(372, 4);
                dew = ReadData.Substring(376, 1);
                dewname = ReadData.Substring(384, 32).Trim();
                Note = ReadData.Substring(416, 336).Trim();
                UID = ReadData.Substring(752, 12).Trim();
                if (dew == "0")
                {
                    labdew.Text = "Chưa tẩy.";
                }
                else
                {
                    if (dew == "1")
                    {
                        labdew.Text = "Đã tẩy.";
                    }
                    else
                    {
                        labdew.Text = "";
                    }
                }
                //xuat
                txtName.Text = Name1;
                txtAddress.Text = Address;
                txtPhone.Text = Phone;
                txtDogName.Text = DogName;
                txtBreed.Text = Breed;
                txtColor.Text = DogColor;
                txtWeight.Text = printhWeight;
                txtVAK.Text = VAK;
                txtDay.Text = VacDay;
                txtMonth.Text = VacMonth;
                txtYear.Text = VacYear;

                txtDayT.Text = DayT;
                txtMonthT.Text = MonthT;
                txtYearT.Text = YearT;
                comboBoxdeworming.Text = dewname;
                comboBoxVaccine.Text = VacName;
                txtDoctor.Text = VacDoc;
                if (ChoiseSex == "1")
                {
                    radioButton1.Checked = true;
                    radioButton2.Checked = false;
                }
                else
                {
                    if (ChoiseSex == "0")
                    {
                        radioButton1.Checked = false;
                        radioButton2.Checked = true;
                    }
                    else
                    {
                        radioButton1.Checked = false;
                        radioButton2.Checked = false;
                    }
                }
                comboBoxDay.Text = ChoiseDay;
                comboBoxMonth.Text = ChoiseMonth;
                comboBoxYear.Text = ChoiseYear;

                txtNote.Text = Note;
                if (System.IO.File.Exists(Application.StartupPath + "\\Data\\" + UID + ".jpg"))
                {
                    pictureBox2.Image = new Bitmap(Application.StartupPath + "\\Data\\" + UID + ".jpg");
                }
                else
                {
                    timer2.Enabled = false;
                    MessageBox.Show("Bạn chưa lưu trữ ảnh của chó. Bạn có thể tải lên một hình ảnh của chó tại nút \"Chọn ảnh\", và lưu ảnh lên hệ thống với nút \"Lưu ảnh\"!", "Thông báo");

                }
                timer2.Enabled = false;
            }
            else
            {
                if (Doc == true)
                {
                    Doc = false;
                    //
                    Name1 = "";
                    Address = "";
                    Phone = "";
                    DogName = "";
                    Breed = "";
                    DogColor = "";
                    printhWeight = "";
                    ChoiseSex = "2";
                    ChoiseDay = "";
                    ChoiseMonth = "";
                    ChoiseYear = "";
                    VAK = "";
                    VacDay = "";
                    VacMonth = "";
                    VacYear = "";
                    labVac.Text = "";

                    VacName = "";
                    VacDoc = "";
                    DayT = "";
                    MonthT = "";
                    YearT = "";
                    dewname = "";
                    Note = "";
                    labdew.Text = "";
                    
                    MessageBox.Show("Đã xảy ra lỗi trong quá trình đọc thẻ. Bạn nên giữ thẻ ổn định, áp sát vào đầu đọc thẻ.", "Thông báo");
                    timer2.Enabled = false;
                }
            }
            
            
            
            
            
        }
        private void DataReceive(object obj, SerialDataReceivedEventArgs e)
        {
            InputData = serialPort1.ReadExisting();
            if (InputData != String.Empty)
            {
                // textbox1 = InputData; // Ko dùng đc như thế này vì khác threads .
                SetText(InputData); //Chính vì vậy phải sử dụng ủy quyền tại đây. Gọi delegate đã khai báo trước đó.
            }
        }

        private void SetText(string text)
        {
            if (this.txtName.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText); // khởi tạo 1 delegate mới gọi đến SetText
                this.Invoke(d, new object[] { text });
            }
            else ReadData += text;                        
        }
        
        private void button5_Click(object sender, EventArgs e)
        {
          if (serialPort1.IsOpen)
          {
                string b="";
            serialPort1.Write("4");
            Thread.Sleep(200);
            //Name 32
            
            int Dodai = txtName.Text.Length;
            if (Dodai <= 32)
            {
                b = txtName.Text; // Name
                for (int i = 0; i < 32 - Dodai; i++)
                {
                    b = b + " ";
                }
            }
            else
            {
                MessageBox.Show("Tên có độ dài lớn hơn 32 Ký Tự.", "Thông báo");
            }
            //////
            Dodai = txtAddress.Text.Length;
            if (Dodai <= 96)
            {
                b = b+txtAddress.Text; // Address
                for (int i = 0; i < 96 - Dodai; i++)
                {
                    b = b + " ";
                }
            } else {
                MessageBox.Show("Địa chỉ có độ dài lớn hơn 96 Ký Tự.", "Thông báo");
            }
            //Phone
            b = b + txtPhone.Text;
            Dodai = txtPhone.Text.Length;
            for (int i = 0; i < 16 - Dodai; i++)
            {
                b = b + " ";
            }
            //DogName
            Dodai = txtDogName.Text.Length;
            if (Dodai <= 32)
            {
                b = b + txtDogName.Text; // Address
                for (int i = 0; i < 32 - Dodai; i++)
                {
                    b = b + " ";
                }
            }
            else
            {
                MessageBox.Show("Tên chó có độ dài lớn hơn 32 Ký Tự.", "Thông báo");
            }
            //Breed
            Dodai = txtBreed.Text.Length;
            if (Dodai <= 48)
            {
                b = b + txtBreed.Text; // Address
                for (int i = 0; i < 48 - Dodai; i++)
                {
                    b = b + " ";
                }
            }
            else
            {
                MessageBox.Show("Giống chó có độ dài lớn hơn 48 Ký Tự.", "Thông báo");
            }
            //Color
            Dodai = txtColor.Text.Length;
            if (Dodai <= 32)
            {
                b = b + txtColor.Text; // Address
                for (int i = 0; i < 32 - Dodai; i++)
                {
                    b = b + " ";
                }
            }
            else
            {
                MessageBox.Show("Màu lông có độ dài lớn hơn 32 Ký Tự.", "Thông báo");
            }
            double Cannang;
            if (txtWeight.Text!= "")
            {
                Cannang = double.Parse(txtWeight.Text);
            }
            else
            {
                Cannang = 0;
            }
            Cannang=Math.Round(Cannang, 1);
            string Can="";
            if (Cannang < 1000)
            {
                Cannang = Cannang * 10;
                Can = Cannang.ToString();
                Dodai = Can.Length;
                for (byte i = 0; i < 4 - Dodai; i++)
                {
                    Can = "0" + Can;
                }
                //MessageBox.Show(Can);
            }
            else
            {
                MessageBox.Show("Chó của bạn nặng trên 1000 Kg?!", "Thông báo");
            }
            b = b + Can;
            string sex="";
            if (radioButton1.Checked == true)
                sex = "1";
            else if (radioButton2.Checked == true)
                sex = "0";
            b = b + sex;
            // Ngay sinh
            string Day = comboBoxDay.Text;
            string Month = comboBoxMonth.Text;
            string Year = comboBoxYear.Text;
            b=b+ Day + Month + Year +"   ";
            //VAK
            Dodai = txtVAK.Text.Length;
            if (Dodai <= 16)
            {
                b = b + txtVAK.Text; //
                for (int i = 0; i < 16 - Dodai; i++)
                {
                    b = b + " ";
                }
            }
            else
            {
                MessageBox.Show("Số đăng ký VAK có độ dài lớn hơn 16 Ký Tự.", "Thông báo");
            }
            //Note
            Dodai = txtNote.Text.Length;
            if (Dodai <= 336)
            {
                b = b + txtNote.Text; // Address
                for (int i = 0; i < 336 - Dodai; i++)
                {
                    b = b + " ";
                }
            }
            else
            {
                MessageBox.Show("Ghi chú của Bác sĩ có độ dài lớn hơn 336 Ký Tự.", "Thông báo");
            }
            // Ket thuc chuoi ky tu bang #
            b = b + '#';
            serialPort1.Write(b);
            //MessageBox.Show(b);
          }
          else if (!serialPort1.IsOpen)
          {
              MessageBox.Show("Chưa kết nối thiết bị với máy tính.", "Thông báo");
          }
        }
        public String Xoakhoangtrang(String Chuoi)
        {
            while (Chuoi.IndexOf("  ") >= 0)    //tim trong chuoi vi tri co 2 khoang trong tro len      
                Chuoi = Chuoi.Replace("  ", " ");   //sau do thay the bang 1 khoang trong     
            return Chuoi;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            serialPort1.Write("7");
            Thread.Sleep(200);
        }
        private void button4_Click_1(object sender, EventArgs e)
        {
          if (serialPort1.IsOpen)
          {
            //MessageBox.Show(comboBoxMonth.Text);
            bien1 = "";
            Form3 Tay = new Form3(comboBoxdeworming.Text);
            Tay.ShowDialog();
            serialPort1.Write("6");
            Thread.Sleep(200);
            //MessageBox.Show(bien1);
            serialPort1.Write(bien1);
          }
          else if (!serialPort1.IsOpen)
          {
              MessageBox.Show("Chưa kết nối thiết bị với máy tính.","Thông báo");
          }
        }
        private void button3_Click_1(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                bien = "";
                Form2 Tiem = new Form2(comboBoxVaccine.Text, txtDoctor.Text);
                Tiem.ShowDialog();

                serialPort1.Write("5");
                Thread.Sleep(200);
                //MessageBox.Show(bien);
                serialPort1.Write(bien);
            }
            else if (!serialPort1.IsOpen)
            {
                MessageBox.Show("Chưa kết nối thiết bị với máy tính.", "Thông báo");
            }
        }
        private void buttonNew_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("7");
                Thread.Sleep(200);
            }
            else if (!serialPort1.IsOpen)
            {
                MessageBox.Show("Chưa kết nối thiết bị với máy tính.", "Thông báo");
            }
        }

        
        //
        private void button_ChonAnh_Click(object sender, EventArgs e)
        {
            pictureBox2.SizeMode = PictureBoxSizeMode.Zoom;
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = "Select Picture";
            openFileDialog.Filter = "All Files|*.*";
            DialogResult result = openFileDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                // Lấy hình ảnh
                ima = Image.FromFile(openFileDialog.FileName);

                // Gán ảnh
                pictureBox2.Image = ima;
                //pictureBox2.Height = 360;
                //pictureBox2.Width = 320;
            }
        }
        //
        
        //
        private void button_LuuAnh_Click(object sender, EventArgs e)
        
        {
            //Image img = pictureBox2.Image;
            //ima.Dispose();
            //string oldfilename = Application.StartupPath + "\\Data\\" + UID + ".jpg";
            
            //pictureBox2.Dispose(); // When I use This After The Function Executed
                                 //PictureBox Disappears But File Delete Successfully.
            
            //File.Save(ima, System.Drawing.Imaging.ImageFormat.Jpeg);       
            if (System.IO.File.Exists(Application.StartupPath + "\\Data\\" + UID + ".jpg"))
            {

                System.GC.Collect();
                System.GC.WaitForPendingFinalizers();
                System.GC.Collect();
                System.GC.WaitForPendingFinalizers();
                System.IO.File.Delete(Application.StartupPath + "\\Data\\" + UID + ".jpg");
            }
            pictureBox2.Image.Save(Application.StartupPath + "\\Data\\" + UID + ".jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
            MessageBox.Show("Đã lưu trữ ảnh của chó!", "Thông báo");
            
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
        //
    }
}
