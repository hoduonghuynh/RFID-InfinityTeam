﻿using System;
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
    public partial class Form2 : Form
    {
        public Form2(string Vac, string Doctor)
        {
            InitializeComponent();
            labMedi.Text = Vac;
            labDoctor.Text = Doctor;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            int day = DateTime.Now.Day;
            int month = DateTime.Now.Month;
            int year = DateTime.Now.Year;
            String date = "";
            if (day < 10)
                date += "0" + day.ToString();
            else
                date += day.ToString();
            date += "/";
            if (month < 10)
                date += "0" + month.ToString();
            else
                date += month.ToString();
            date += "/";
            date += year.ToString();
            labDate.Text = date;
            
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

            string b = "";
            int day = DateTime.Now.Day;
            int month = DateTime.Now.Month;
            int year = DateTime.Now.Year;
            String Sday, Smonth;
            if (day < 10)
            {
                Sday = " " + day;
            }
            else
            {
                Sday = day.ToString();
            }
            if (month < 10)
            {
                Smonth = " " + month;
            }
            else
            {
                Smonth = month.ToString();
            }
            b = b + Sday + Smonth + year + "1       ";
            int Dodai;
            Dodai = labMedi.Text.Length;            
            b = b + labMedi.Text;
            for (int i = 0; i < 32 - Dodai; i++)
            {
                b = b + " ";
            }
            Dodai = labDoctor.Text.Length;
            b = b + labDoctor.Text;
            for (int i = 0; i < 32 - Dodai; i++)
            {
                b = b + " ";
            }
            b = b + "#";
            Form1.bien = b;
            this.Close();
            
            
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
