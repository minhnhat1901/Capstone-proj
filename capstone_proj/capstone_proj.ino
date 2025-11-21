// #include <DFRobotDFPlayerMini.h>
// #include "motor_control.h"

// const int PIR_PIN = 34;

// bool pir_state = LOW; // PIR state change
// int motion_status = LOW; // current pin reading

// DFRobotDFPlayerMini fxPlayer;

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   delay(500);

//   pinMode(PIR_PIN, INPUT);

//   Serial1.begin(9600);
//   delay(200);

//   Serial.println("Initializing DFPlayer…");
//   if (!fxPlayer.begin(fxSerial)) {
//     Serial.println("DFPlayer init failed! Check wiring and SD card.");
//     return;
//   }
  
//   Serial.println("DFPlayer ready.");

//   fxPlayer.begin(Serial1);
  
//   // Can set from 0 - 30
//   fxPlayer.volume(20);
//   delay(5000);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   motion_status = digitalRead(PIR_PIN);

//   if (motion_status == HIGH && pir_state == LOW) {
//     Serial.println("Motion Detected");
//     pir_state = HIGH;

//     // Add below things want to activate
//     Serial.println("Playing track 1...");
//     fxPlayer.play(1);
//     delay(2500);
//   }
//   if (motion_status == LOW && pir_state == HIGH) {
//     Serial.println("Motion Ended");
//     pir_state = LOW;

//     // Add below things want to deactivate
//     Serial.println("Playing track 2...");
//     fxPlayer.play(2);
//     delay(2200);
//   }

//   delay(50);
// }

// This code is using to control the clothesline
// void setup()
// {
//   pinMode(forwardPin, OUTPUT);
//   pinMode(backwardPin, OUTPUT);
//   delay(1000);
// }

// void loop()
// {
//   bringoutMove();
//   speedControl(200,0);
//   delay(delayTime);
  
//   stopMove();
//   delay(stopTime);
  
//   bringinMove();
//   speedControl(0, 200);
//   delay(delayTime);

//   stopMove();
//   delay(stopTime);
// }

//Arduino Code - RC522 Read RFID Tag UID

#include <SPI.h>
#include <MFRC522.h>

// #define SS_PIN 10
// #define RST_PIN 9
 
MFRC522 mfrc522(10, 9); // Instance of the class

// MFRC522::MIFARE_Key key; 

void setup() { 
  pinMode(6, OUTPUT); pinMode(7, OUTPUT); pinMode(8, OUTPUT);
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init RC522 
  Serial.println("Bring your card close to the reader");
  Serial.println("-----------------------------------");
}
 
void loop() {
  digitalWrite(6, LOW); digitalWrite(7, LOW); digitalWrite(8, LOW); 
  if (!mfrc522.PICC_IsNewCardPresent())
    return;

  if (!mfrc522.PICC_ReadCardSerial())
    return;

  // MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  Serial.print(F("RFID Tag UID:"));
  String card = printHex(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(card);

  if (card == "1E70463") {
    authorizedAccess();
  } else {
    accessDenied();
  }

  // mfrc522.PICC_HaltA(); // Halt PICC
}

//  Routine to dump a byte array as hex values to Serial. 
String printHex(byte *buffer, byte bufferSize) {
  String card_id = "";

  for (byte i = 0; i < bufferSize; i++) {
    card_id.concat(String(buffer[i], HEX));
  }

  card_id.toUpperCase();

  return card_id;
}

void authorizedAccess() {
  Serial.println();
  Serial.println("Message: Authorized Access");
  digitalWrite(6, HIGH);
  for (byte i = 0; i < 3; i++) {
    digitalWrite(8, HIGH); delay(200);
    digitalWrite(8, LOW); delay(200);
  }
}

void accessDenied() {
  Serial.println();
  Serial.println("Message: Access Denied");
  digitalWrite(7, HIGH);
  for (byte i = 0; i < 3; i++) {
    digitalWrite(8, HIGH);
    delay(1000);
  }
}
