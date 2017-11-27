void Guitinnhan(){
    GPRS.write("AT+CMGF=1\r"); //sending SMS in text mode
    delay(300);
    //Serial.println("AT+CMGF=1\r");
    //GPRS.write(Phone); // phone number
    //Serial.println(Phone);
    GPRS.print("AT+CMGS=\"+84"+Phone+"\"\r\n");
    delay(300);
    //Serial.println(Phone);
    GPRS.print("Chi cuc Thu Y Tp.HCM xin thong bao den anh/chi "+ Name+": thu cung cua anh/chi ("+DogName+") da bi Cuc thu y bat theo quy dinh phap luat. Tinh trang tiem phong benh dai: "+ Dai +" tiem, muc tien phat theo quy dinh la: "+ Tien+" VND. De nghi anh/chi den dia chi: 252 Ly Chinh Thang, Quan 3, Tp.HCM de nop phat va nhan lai thu cung trong vong 72 gio ke tu khi nhan duoc tin nhan nay.\r"); // message
    delay(300);
    //Serial.println("Hi! My name Arduino!\r"); 
    delay(300);
    GPRS.write(0x1A);
    //send a Ctrl+Z (end of the message)
    delay(300);
    //Serial.println("SMS sent successfully");
    Phone="";
    DogName="";
    Name="";
    bit_bit();
}
/////////
void clearBufferArray(){
  // function to clear buffer array
  for (int i=0; i<count;i++){
    buffer[i]='\0';
  }
}

