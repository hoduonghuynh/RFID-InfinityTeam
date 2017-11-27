void ReadBlock(byte block){
  MFRC522::MIFARE_Key keyA;
  keyA.keyByte[5]=0x27;
  keyA.keyByte[4]=0x01;
  keyA.keyByte[3]=0x96;
  keyA.keyByte[2]=0xFE;
  keyA.keyByte[1]=0xFA;
  keyA.keyByte[0]=0xEE;
  byte buffer1[18];
  byte len=18;
  MFRC522::StatusCode status;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid));
  //So sanh Key A duoc dat tren the co giong voi key duoc dat truoc trong phan mem hay khong
  if (status != MFRC522::STATUS_OK) { // Neu sai thi bao loi, doc lai bien status
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //Thuc hien kiem tra du lieu ghi len the co hop le hay khong.
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) { // Neu sai thi bao loi
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //Thuc hien viec ghi du lieu len the.
  for (uint8_t i = 0; i < 16; i++)
  {
      Serial.write(buffer1[i]);
  }
}

