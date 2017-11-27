void ReadData(){
  // Tim mot the moi trong khu vuc
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Chon mot the
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  byte buffer1[18]; // Mang chua cac gia tri doc duoc tu block
  //ReadBlock(A); Đọc dữ liệu ở Block A sau đó xuất ra Serial
  ReadBlock(1);
  ReadBlock(2);
  ReadBlock(4);
  ReadBlock(5);
  ReadBlock(6);
  ReadBlock(8);
  ReadBlock(9);
  ReadBlock(10);
  ReadBlock(12);
  ReadBlock(13);
  ReadBlock(14);
  ReadBlock(16);
  ReadBlock(17);
  ReadBlock(18);
  ReadBlock(20);
  ReadBlock(21);
  ReadBlock(22);
  ReadBlock(24);
  ReadBlock(28);
  ReadBlock(29);
  ReadBlock(30);
  ReadBlock(25);
  ReadBlock(26);
  ReadBlock(32);
  ReadBlock(33);
  ReadBlock(34);
  ReadBlock(36);
  ReadBlock(37);
  ReadBlock(38);
  ReadBlock(40);
  ReadBlock(41);
  ReadBlock(42);
  ReadBlock(44);
  ReadBlock(45);
  ReadBlock(46);
  ReadBlock(48);
  ReadBlock(49);
  ReadBlock(50);
  ReadBlock(52);
  ReadBlock(53);
  ReadBlock(54);
  ReadBlock(56);
  ReadBlock(57);
  ReadBlock(58);
  ReadBlock(60);
  ReadBlock(61);
  ReadBlock(62);
  for (byte i = 0; i < 4; i++) {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    if (mfrc522.uid.uidByte[i]<10) {
      Serial.print("00");      
    } else {
      if (mfrc522.uid.uidByte[i]<100) {
        Serial.print("0");
      } 
    }
    Serial.print(mfrc522.uid.uidByte[i]);
  } 
  Serial.print("#"); // Ky tu danh dau ket thuc viec duoc du lieu
  delay(100); //change value if you want to read cards faster
  //Ket thuc qua trinh ghi/doc the
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  //Bao coi hoan thanh viec ghi/doc du lieu
  bit_bit();
}


