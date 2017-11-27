void Tiemphong(){
  char VacDate[16];
  char VacName1[16];
  char VacName2[16];
  char VacDoc1[16];
  char VacDoc2[16];
  char buffer[90];
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
  int len;
  len = Serial.readBytesUntil('#', (char *) buffer, 90) ; // read family name from serial
  for (int i = len; i < 90; i++) buffer[i] = ' '; 
  for (byte i=0; i<16; i++) {
    VacDate[i]=   buffer[i];
    VacName1[i]=  buffer[16+i];
    VacName2[i]=  buffer[16+16+i];
    VacDoc1[i]=   buffer[16+16+16+i];
    VacDoc2[i]=   buffer[16+16+16+16+i];
  }
  //////////////
  WriteBlock(28, VacDate);
  WriteBlock(29, VacName1);
  WriteBlock(30, VacName2);
  WriteBlock(25, VacDoc1);
  WriteBlock(26, VacDoc2);
  //Ket thuc qua trinh ghi/doc the
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  //Bao coi hoan thanh viec ghi/doc du lieu
  bit_bit();
}

