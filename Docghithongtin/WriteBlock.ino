void WriteBlock(byte block,   byte buffer1[16]) {
  MFRC522::MIFARE_Key keyA;
  keyA.keyByte[5]=0x27;
  keyA.keyByte[4]=0x01;
  keyA.keyByte[3]=0x96;
  keyA.keyByte[2]=0xFE;
  keyA.keyByte[1]=0xFA;
  keyA.keyByte[0]=0xEE;
  MFRC522::StatusCode status;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    //Serial.print(F("PCD_Authenticate() failed: "));
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Write(block, buffer1, 16);
  if (status != MFRC522::STATUS_OK) {
    //Serial.print(F("MIFARE_Write() failed: "));
    //Serial.println(mfrc522.GetStatusCodeName(status));
    //bit_bit();
    return;
  }
}

