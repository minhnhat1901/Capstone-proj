// // #include "secured_control.h"

// // SecuredControl::SecuredControl() {
// //     // Constructor implementation (if needed)
// // }

// // //  Routine to dump a byte array as hex values to Serial.
// // String SecuredControl::printHex(byte *buffer, byte bufferSize) {
// //     String card_id = "";

// //     for (byte i = 0; i < bufferSize; i++) {
// //         card_id.concat(String(buffer[i], HEX));
// //     }

// //     card_id.toUpperCase();

// //     return card_id;
// // }

// // void SecuredControl::authorizedAccess() {
// //     Serial.println();
// //     Serial.println("Message: Authorized Access");
// //     myservo.write(90);

// //     Serial.println("Playing track 1...");
// //     fxPlayer.play(1);
// //     delay(3000);
// //     myservo.write(0);
// //     delay(500);
// // }

// // void SecuredControl::accessDenied() {
// //     Serial.println();
// //     Serial.println("Message: Access Denied");
// //     if (count < 2) {
// //         Serial.println("Playing track 2...");
// //         fxPlayer.play(2);
// //         delay(2500);
// //     }
// // }

// #include "secured_control.h"

// // Constructor: initialize MFRC522 with your original pins
// SecuredControl::SecuredControl()
//   : mfrc522(MFRC_SS_PIN, MFRC_RST_PIN) {
//   // nothing else needed here
// }

// // This was your original setup() logic
// void SecuredControl::begin() {
//   Serial.begin(9600);
//   delay(500);

//   pinMode(PIR_PIN, INPUT);

//   Serial1.begin(9600);
//   delay(2000);

//   Serial.println("Initializing DFPlayer…");
//   if (!fxPlayer.begin(Serial1)) {
//     Serial.println("DFPlayer init failed! Check wiring and SD card.");
//     while (true) {
//       delay(1000);
//     }
//   }

//   Serial.println("DFPlayer ready.");

//   myservo.attach(SERVO_PIN);
//   myservo.write(0);

//   SPI.begin();           // Init SPI bus
//   mfrc522.PCD_Init();    // Init RC522

//   // Can set from 0 - 30
//   fxPlayer.volume(20);
//   delay(5000);

//   Serial.println("Bring your card close to the reader");
//   Serial.println("-----------------------------------");
// }

// // This was your original loop() logic
// void SecuredControl::update() {
//   motion_status = digitalRead(PIR_PIN);

//   if (motion_status == HIGH && pir_state == LOW) {
//     Serial.println("Motion Detected");
//     count = 0;

//     do {
//       if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
//         continue;
//       }

//       String card = printHex(mfrc522.uid.uidByte, mfrc522.uid.size);

//       if (card == "1E70463") {
//         authorizedAccess();
//         break;
//       } else {
//         accessDenied();
//         count++;
//       }

//       Serial.print(F("RFID Tag UID:"));
//       Serial.println(card);

//       mfrc522.PICC_HaltA(); // Halt PICC
//     } while (count < 3);

//     if (count == 3) {
//       Serial.println("Playing track 3...");
//       fxPlayer.play(3);
//       delay(2500);
//     }

//     pir_state = HIGH;
//   }

//   if (motion_status == LOW && pir_state == HIGH) {
//     Serial.println("Motion Ended");
//     pir_state = LOW;
//   }

//   delay(50);
// }

// //  Routine to dump a byte array as hex values to Serial.
// //  (same logic as your original printHex)
// String SecuredControl::printHex(byte *buffer, byte bufferSize) {
//   String card_id = "";

//   for (byte i = 0; i < bufferSize; i++) {
//     card_id.concat(String(buffer[i], HEX));
//   }

//   card_id.toUpperCase();

//   return card_id;
// }

// // Same logic as your original authorizedAccess()
// void SecuredControl::authorizedAccess() {
//   Serial.println();
//   Serial.println("Message: Authorized Access");
//   myservo.write(90);

//   Serial.println("Playing track 1...");
//   fxPlayer.play(1);
//   delay(3000);
//   myservo.write(0);
//   delay(500);
// }

// // Same logic as your original accessDenied()
// void SecuredControl::accessDenied() {
//   Serial.println();
//   Serial.println("Message: Access Denied");
//   if (count < 2) {
//     Serial.println("Playing track 2...");
//     fxPlayer.play(2);
//     delay(2500);
//   }
// }
