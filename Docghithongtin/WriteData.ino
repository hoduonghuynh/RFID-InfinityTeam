void WriteData(){
  char Name1[16];
  char Name2[16];
  char Address1[16];
  char Address2[16];
  char Address3[16];
  char Address4[16];
  char Address5[16];
  char Address6[16];
  char Phone[16];
  char DogName1[16];
  char DogName2[16];
  char Breed1[16];
  char Breed2[16];
  char Breed3[16];
  char Color1[16];
  char Color2[16];
  char Block22[16];
  char VAK[16];
  char Note1[16];
  char Note2[16];
  char Note3[16];
  char Note4[16];
  char Note5[16];
  char Note6[16];
  char Note7[16];
  char Note8[16];
  char Note9[16];
  char Note10[16];
  char Note11[16];
  char Note12[16];
  char Note13[16];
  char Note14[16];
  char Note15[16];
  char Note16[16];
  char Note17[16];
  char Note18[16];
  char Note19[16];
  char Note20[16];
  char Note21[16];
  char buffer[752];
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
  len = Serial.readBytesUntil('#', (char *) buffer, 752) ; // Read chuoi tu phan mem C# gui xuong cho arduino
  for (int i = len; i < 752; i++) buffer[i] = ' '; // Neu chuoi duoc gui ngan hon 752 thi ghi phim trang len cac ky tu trong
  //Tach cac thong tin tu chuoi lon thanh cac chuoi nho hon.
  for (byte i=0; i<16; i++) {
    Name1[i]=   buffer[i];
    Name2[i]=   buffer[16+i];
    Address1[i]=buffer[32+i];
    Address2[i]=buffer[48+i];
    Address3[i]=buffer[64+i];
    Address4[i]=buffer[80+i];
    Address5[i]=buffer[96+i];
    Address6[i]=buffer[112+i];
    Phone[i]=   buffer[128+i];
    DogName1[i]=buffer[144+i];
    DogName2[i]=buffer[160+i];
    Breed1[i]=  buffer[176+i];
    Breed2[i]=  buffer[192+i];
    Breed3[i]=  buffer[208+i];
    Color1[i]=  buffer[224+i];
    Color2[i]=  buffer[240+i];
    Block22[i]= buffer[256+i];
    VAK[i]=     buffer[272+i];
    Note1[i]=   buffer[272+16+i];
    Note2[i]=   buffer[272+16+16+i];
    Note3[i]=   buffer[272+16+16+16+i];
    Note4[i]=   buffer[272+16+16+16+16+i];
    Note5[i]=   buffer[272+16+16+16+16+16+i];
    Note6[i]=   buffer[272+16+16+16+16+16+16+i];
    Note7[i]=   buffer[272+16+16+16+16+16+16+16+i];
    Note8[i]=   buffer[272+16+16+16+16+16+16+16+16+i];
    Note9[i]=   buffer[272+16+16+16+16+16+16+16+16+16+i];
    Note10[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+i];
    Note11[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+i];
    Note12[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note13[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note14[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note15[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note16[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note17[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note18[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note19[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note20[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
    Note21[i]=  buffer[272+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+16+i];
  }
 //////////////
 //WriteBLock(A , B); Ghi dữ liệu lên Block A, Nội dung dữ liệu là mảng B
  WriteBlock(1, Name1);
  WriteBlock(2, Name2);
  WriteBlock(4, Address1);
  WriteBlock(5, Address2);
  WriteBlock(6, Address3);
  WriteBlock(8, Address4);
  WriteBlock(9, Address5);
  WriteBlock(10, Address6);
  WriteBlock(12, Phone);
  WriteBlock(13, DogName1);
  WriteBlock(14, DogName2);
  WriteBlock(16, Breed1);
  WriteBlock(17, Breed2);
  WriteBlock(18, Breed3);
  WriteBlock(20, Color1);
  WriteBlock(21, Color2);
  WriteBlock(22, Block22);
  WriteBlock(24, VAK);
  WriteBlock(36, Note1);
  WriteBlock(37, Note2);
  WriteBlock(38, Note3);
  WriteBlock(40, Note4);
  WriteBlock(41, Note5);
  WriteBlock(42, Note6);
  WriteBlock(44, Note7);
  WriteBlock(45, Note8);
  WriteBlock(46, Note9);
  WriteBlock(48, Note10);
  WriteBlock(49, Note11);
  WriteBlock(50, Note12);
  WriteBlock(52, Note13);
  WriteBlock(53, Note14);
  WriteBlock(54, Note15);
  WriteBlock(56, Note16);
  WriteBlock(57, Note17);
  WriteBlock(58, Note18);
  WriteBlock(60, Note19);
  WriteBlock(61, Note20);
  WriteBlock(62, Note21);
  //Ket thuc qua trinh ghi/doc the
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  //Bao coi hoan thanh viec ghi/doc du lieu
  bit_bit();
}

