void Tay(){ //Ghi thong tin tay giun san
  char VacDate[16]; // Thoi gian tay
  char VacName1[16]; //Ten thuoc 1
  char VacName2[16]; //Ten thuoc 2
  char buffer[48];

  int len;
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
  len = Serial.readBytesUntil('#', (char *) buffer, 48) ; // read family name from serial
  for (int i = len; i < 48; i++) buffer[i] = ' '; 
  for (byte i=0; i<16; i++) {
    VacDate[i]=   buffer[i];
    VacName1[i]=  buffer[16+i];
    VacName2[i]=  buffer[16+16+i];
  }
  WriteBlock(32, VacDate);
  WriteBlock(33, VacName1);
  WriteBlock(34, VacName2);
  //Ket thuc qua trinh ghi/doc the
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  //Bao coi hoan thanh viec ghi/doc du lieu
  bit_bit();
}

