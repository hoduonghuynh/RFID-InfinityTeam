#include <SoftwareSerial.h>
#include <string.h>
SoftwareSerial GPRS(7, 6); //7 = TX, 6 = RX
char buffer[64]; //port
String Phone;
String DogName;
String Name;
String Dai, Tien;
int count=0;

int val;
int led = 13;
byte buzzer=8;
////
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN); 
void setup() {
  GPRS.begin(9600); // the GPRS baud rate
  Serial.begin(9600); // the Serial port of Arduino baud rate.
  //Guitinnhan();
  /////////////////////////////
    pinMode(led, OUTPUT);
    pinMode(buzzer, OUTPUT);
    
    SPI.begin();                                                  // Init SPI bus
    mfrc522.PCD_Init();          
    digitalWrite(buzzer, LOW);// Init MFRC522 card
  //Serial.println(F("Read personal data on a MIFARE PICC:"));  
}

void loop() {
  if (GPRS.available()) {
    // if date is coming from softwareserial port ==> data is coming from GPRS shield
    while(GPRS.available()) {
      // reading data into char array
      buffer[count++]=GPRS.read();
      // writing data into array
      if(count == 64)
        break;
    }
    Serial.write(buffer,count);
    // if no data transmission ends, write buffer to hardware serial port
    clearBufferArray();
    // call clearBufferArray function to clear the stored data from the array
    count = 0; // set counter of while loop to zero
  }
  if (Serial.available())
    // if data is available on hardwareserial port ==> data is coming from PC or notebook
    GPRS.write(Serial.read()); // write it to the GPRS shield
    
  MFRC522::MIFARE_Key keyA;
  keyA.keyByte[5]=0x27;
  keyA.keyByte[4]=0x01;
  keyA.keyByte[3]=0x96;
  keyA.keyByte[2]=0xFE;
  keyA.keyByte[1]=0xFA;
  keyA.keyByte[0]=0xEE;
  
  //some variables we need
  byte block;
  const byte len=18;
  MFRC522::StatusCode status;

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  char buffer1[18];
  //Read Phone
  block = 12;
  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //Xu ly Phone.
  if (buffer1[10] == ' ') {
    //Serial.println("Dung");
    for (uint8_t i = 1; i < 10; i++)
    {
      //sdt10[i]=buffer1[i];
      Phone = String(Phone +buffer1[i]);
    }
  } else {
    //Serial.println("Sai");
    for (uint8_t i = 1; i < 11; i++)
    {
      Phone = String(Phone +buffer1[i]);
    }
  }
  //Read DogName
  block = 13;
  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  ///
  for (byte j=0; j<16; j++) {
    if (buffer1[j]==' ' && buffer1[j+1]==' ') { break;}
    DogName = String(DogName + buffer1[j]);
  }
  block = 14;
  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //Xu ly
  for (byte j=0; j<16; j++) {
    if (buffer1[j]==' ' && buffer1[j+1]==' ') { break;}
    DogName = String(DogName + buffer1[j]);
  }
  //Name
  block = 1;
  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //
  for (byte j=0; j<16; j++) {
    if (buffer1[j]==' ' && buffer1[j+1]==' ') { break;}
    Name = String(Name + buffer1[j]);
  }
  //Name
  block = 2;
  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //
  for (byte j=0; j<16; j++) {
    if (buffer1[j]==' ' && buffer1[j+1]==' ') { break;}
    Name = String(Name + buffer1[j]);
  }
  //
    block = 28;
  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keyA, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //
  if (buffer1[8]=='1') {
    Dai="da";
    Tien="600.000";
  } else {
    Dai="chua";
    Tien="2.500.000";
  }
  delay(100); //change value if you want to read cards faster
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  Guitinnhan();
}



