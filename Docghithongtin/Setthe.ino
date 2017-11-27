void Setthe() {
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  // Key mac dinh cua the moi la FFFFFFFFFFFFh
  MFRC522::MIFARE_Key keyA;
  keyA.keyByte[0]=0xFF;
  keyA.keyByte[1]=0xFF;
  keyA.keyByte[2]=0xFF;
  keyA.keyByte[3]=0xFF;
  keyA.keyByte[4]=0xFF;
  keyA.keyByte[5]=0xFF;
   
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
            return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())    return;
    // Dat bien buffer la key cua minh mong muon
    byte buffer[16] = {0xEE, 0xFA, 0xFE, 0x96, 0x01, 0x27, 0xFF, 0x07, 0x80, 0x69, 0x27, 0x01, 0x96, 0xFE, 0xFA, 0xEE}; // He thong
    /////////////
    byte block;
    byte status, len;
    Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
    //Key
    // The duoc chia lam 16 sector nen tao cho chay i tu 1 den 16
    // Ghi du lieu len Key moi len cac block trailer
    for (byte i=1; i<=16; i++) {
      block = i*4-1; // Vi tri cua cac block trailer
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid));
      if (status != MFRC522::STATUS_OK) {
        //Serial.print("PCD_Authenticate() failed: ");
        //Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }   
      // Write block
      status = mfrc522.MIFARE_Write(block, buffer, 16);
      if (status != MFRC522::STATUS_OK) {
        //Serial.print("MIFARE_Write() failed: ");
        //Serial.println(mfrc522.GetStatusCodeName(status));
            return;
      }
    }
  //Key A gio la Key A he thong
  // Tiep theo ta ghi phim trang vao cac block Data 
  byte buffer1[16] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}; // chen khoang trang vao cac block data
  WriteBlock(1, buffer1);
  WriteBlock(2, buffer1);
    //block data
    for (byte i=2; i<=16; i++) {
      WriteBlock(i*4-1-1, buffer1);
      WriteBlock(i*4-1-2, buffer1);
      WriteBlock(i*4-1-3, buffer1);
    }
    //////////
    //Ket thuc qua trinh ghi/doc the
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
    //Bao coi hoan thanh viec ghi/doc du lieu
    bit_bit();
}
