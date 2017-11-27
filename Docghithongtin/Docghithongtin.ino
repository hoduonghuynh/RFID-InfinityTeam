int val;
byte buzzer=8;
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN); 
void setup() {
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    SPI.begin();                                                  // Init SPI bus
    mfrc522.PCD_Init();          
    digitalWrite(buzzer, LOW);// Init MFRC522 card
}
void loop() {
    val=Serial.read();
    switch (val) {
      case '3':
        ReadData();
        break;
      case '4':
        WriteData();
        break;
      case '5':
        Tiemphong();
        break;
      case '6':
        Tay();
        break;
      case '7':
        Setthe();
        break;
      default:
        break;
    }
}
