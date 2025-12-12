#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

/***
  *  Sound track:
      - 1 --> Welcome to paradise
      - 2 --> Try again
      - 3 --> Get out of here 
      - 4 --> Hello
*/

// ---- Pin assignments for Arduino Uno ----
const int PIR_PIN    = 7;   // PIR output (changed from 34 -> 7)
const int SERVO_PIN  = 8;   // Servo pin (changed from 22 -> 8)

// DFPlayer Mini via SoftwareSerial
const int RX_PIN  = 3;
const int TX_PIN  = 2;

bool pir_state = 0;       // PIR state change
int  motion_status = LOW;   // current pin reading
int  count = 0;

SoftwareSerial fxSerial(RX_PIN, TX_PIN); // RX, TX
DFRobotDFPlayerMini fxPlayer;
Servo myservo;

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID on Uno SPI pins

void setup() {
  Serial.begin(9600);
  delay(500);

  pinMode(PIR_PIN, INPUT);
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);

  // DFPlayer serial on SoftwareSerial
  fxSerial.begin(9600);
  delay(2000);  // give the DFPlayer time to boot

  Serial.println("Initializing DFPlayer…");
  if (!fxPlayer.begin(fxSerial)) {
    Serial.println("DFPlayer init failed! Check wiring and SD card.");
    while (true) { delay(1000); }  // stop here if DFPlayer not found
  }
  Serial.println("DFPlayer ready.");

  myservo.attach(SERVO_PIN);
  myservo.write(61);

  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init RC522 

  // Can set from 0 - 30
  fxPlayer.volume(30);
  delay(5000);

  Serial.println("Bring your card close to the reader");
  Serial.println("-----------------------------------");
}

void loop() {
  motion_status = digitalRead(PIR_PIN);

  if (motion_status == HIGH && pir_state == LOW) {
    Serial.println("Motion Detected");

    Serial.println();
    Serial.println("Message: Person Detected");
    
    Serial.println("Playing track 4...");
    fxPlayer.play(4);
    delay(3000);

    count = 0;

    do {
      // wait for a valid card
      if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
        continue;

      String card = printHex(mfrc522.uid.uidByte, mfrc522.uid.size);

      if (card == "1E70463") {
        authorizedAccess();
        break;
      } else {
        accessDenied();
        count++;
      }

      Serial.print(F("RFID Tag UID:"));
      Serial.println(card);

      mfrc522.PICC_HaltA(); // Halt PICC
    } while (count < 3);
    
    if (count == 3) {
      Serial.println("Playing track 3...");
      fxPlayer.play(3);
      delay(2500);
    }

    pir_state = HIGH;
    // Add below things want to activate
  }

  if (motion_status == LOW && pir_state == HIGH) {
    Serial.println("Motion Ended");
    pir_state = LOW;
  }

  delay(50);
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
  myservo.write(180);

  Serial.println("Playing track 1...");
  fxPlayer.play(1);
  delay(5000);

  myservo.write(61);
  delay(500);
}

void accessDenied() {
  Serial.println();
  Serial.println("Message: Access Denied");
  if (count < 2) {   // only for first 2 failed attempts
    Serial.println("Playing track 2...");
    fxPlayer.play(2);
    delay(2500);
  }
}
