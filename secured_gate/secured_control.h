#ifndef SECURED_CONTROL_H
#define SECURED_CONTROL_H

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 10
#define RST_PIN 9

void loop() {
  // put your main code here, to run repeatedly:
    motion_status = digitalRead(PIR_PIN);

    if (motion_status == HIGH && pir_state == LOW) {
    Serial.println("Motion Detected");
    count = 0;
    do {
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
    }
    if (motion_status == LOW && pir_state == HIGH) {
        Serial.println("Motion Ended");
        pir_state = LOW;
    }

    delay(50);
}

class SecuredControl {
    public:
        SecuredControl();
        String printHex(byte *buffer, byte bufferSize);
        void authorizedAccess();
        void accessDenied();

    private:
        int PIR_PIN = 34;
        bool pir_state = LOW; // PIR state change
        int motion_status = LOW; // current pin reading
        int count = 0;

        int SS_PIN = 10;
        int RST_PIN = 9;
};

// This code is using to control the clothesline

void loop() {
  int value = analogRead(sensorVal);
  Serial.print("Value: ");
  Serial.println(value);
  delay(100);

  if (value < 800) {
    digitalWrite(ledSignal, HIGH);
    Serial.println("It's raining!!!");

    if (!hasBroughtIn) {
      bringinMove();
      speedControl(0, 200);
      delay(delayTime);

      hasBroughtIn = true;
      hasBroughtOut = false;
    }

    stopMove();
    delay(stopTime);
  } else {
    digitalWrite(ledSignal, LOW);
    Serial.println("No rain!!!");

    if (!hasBroughtOut) {
      bringoutMove();
      speedControl(150, 0);
      delay(delayTime);

      hasBroughtOut = true;
      hasBroughtIn = false;
    }

    stopMove();
    delay(stopTime);
  }
}

#endif