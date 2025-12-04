// #include <DFRobotDFPlayerMini.h>
// #include <SPI.h>
// #include <MFRC522.h>
// #include <Servo.h>

// #define SS_PIN 10
// #define RST_PIN 9

// const int PIR_PIN = 34;

// bool pir_state = LOW; // PIR state change
// int motion_status = LOW; // current pin reading
// int count = 0;

// DFRobotDFPlayerMini fxPlayer;
// Servo myservo;  // create servo object to control a servo

// MFRC522 mfrc522(53, 49); // Instance of the class

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   delay(500);

//   pinMode(PIR_PIN, INPUT);

//   Serial1.begin(9600);
//   delay(2000);

//   Serial.println("Initializing DFPlayer…");
//   if (!fxPlayer.begin(Serial1)) {
//     Serial.println("DFPlayer init failed! Check wiring and SD card.");
//     while(true) { delay(1000); }
//   }

//   Serial.println("DFPlayer ready.");

//   myservo.attach(22);
//   myservo.write(0);

//   SPI.begin(); // Init SPI bus
//   mfrc522.PCD_Init(); // Init RC522

//   // Can set from 0 - 30
//   fxPlayer.volume(20);
//   delay(5000);


//   Serial.println("Bring your card close to the reader");
//   Serial.println("-----------------------------------");
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   motion_status = digitalRead(PIR_PIN);

//   if (motion_status == HIGH && pir_state == LOW) {
//     Serial.println("Motion Detected");
//     count = 0;
//     do {
//       if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
//         continue;

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
//     // Add below things want to activate

//   }
//   if (motion_status == LOW && pir_state == HIGH) {
//     Serial.println("Motion Ended");
//     pir_state = LOW;

//     // Add below things want to deactivate
//     // Serial.println("Playing track 2...");
//     // fxPlayer.play(2);
//     // delay(2200);
//   }

//   delay(50);
// }

// //  Routine to dump a byte array as hex values to Serial.
// String printHex(byte *buffer, byte bufferSize) {
//   String card_id = "";

//   for (byte i = 0; i < bufferSize; i++) {
//     card_id.concat(String(buffer[i], HEX));
//   }

//   card_id.toUpperCase();

//   return card_id;
// }

// void authorizedAccess() {
//   Serial.println();
//   Serial.println("Message: Authorized Access");
//   myservo.write(90);

//   Serial.println("Playing track 1...");
//   fxPlayer.play(1);
//   delay(3000);
//   myservo.write(0);
//   delay(500);
// }

// void accessDenied() {
//   Serial.println();
//   Serial.println("Message: Access Denied");
//   if (count < 2) {
//     Serial.println("Playing track 2...");
//     fxPlayer.play(2);
//     delay(2500);
//   }
// }

// This code is using to control the clothesline

// void loop() {
//   int value = analogRead(sensorVal);
//   Serial.print("Value: ");
//   Serial.println(value);
//   delay(100);

//   if (value < 800) {
//     digitalWrite(ledSignal, HIGH);
//     Serial.println("It's raining!!!");

//     if (!hasBroughtIn) {
//       bringinMove();
//       speedControl(0, 200);
//       delay(delayTime);

//       hasBroughtIn = true;
//       hasBroughtOut = false;
//     }

//     stopMove();
//     delay(stopTime);
//   } else {
//     digitalWrite(ledSignal, LOW);
//     Serial.println("No rain!!!");

//     if (!hasBroughtOut) {
//       bringoutMove();
//       speedControl(150, 0);
//       delay(delayTime);

//       hasBroughtOut = true;
//       hasBroughtIn = false;
//     }

//     stopMove();
//     delay(stopTime);
//   }
// }