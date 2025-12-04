#include "motor_control.h"

ClotheslineControl::ClotheslineControl() {
  hasBroughtIn = false;
  hasBroughtOut = false;
}

ClotheslineControl::ClotheslineControl(int ledPin, int backPin, int forePin, int sensorPin) 
  : ledSignal(ledPin), backwardPin(backPin), forwardPin(forePin), sensorVal(sensorPin) {
  hasBroughtIn = false;
  hasBroughtOut = false;
}

void ClotheslineControl::speedControl(int speed1, int speed2) {
  analogWrite(forwardPin, speed1);
  analogWrite(backwardPin, speed2);
}

void ClotheslineControl::stopMove() {
  digitalWrite(forwardPin, LOW);
  digitalWrite(backwardPin, LOW);
}

void ClotheslineControl::bringoutMove() {
  digitalWrite(forwardPin, HIGH);
  digitalWrite(backwardPin, LOW);
}

void ClotheslineControl::bringinMove() {
  digitalWrite(forwardPin, LOW);
  digitalWrite(backwardPin, HIGH);
}

void ClotheslineControl::execute(int value) {
  if (value < 800) {
    digitalWrite(ledSignal, HIGH);
    Serial.println("It's raining!!!");

    if (!hasBroughtIn) {
      bringinMove();
      speedControl(0, 200);
      delay(DELAYTIME);

      hasBroughtIn = true;
      hasBroughtOut = false;
    }

    stopMove();
    delay(STOPTIME);
  } else {
    digitalWrite(ledSignal, LOW);
    Serial.println("No rain!!!");

    if (!hasBroughtOut) {
      bringoutMove();
      speedControl(150, 0);
      delay(DELAYTIME);

      hasBroughtOut = true;
      hasBroughtIn = false;
    }

    stopMove();
    delay(STOPTIME);
  }
}