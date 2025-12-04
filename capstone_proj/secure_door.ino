#include "motor_control.h"

const int ledSignal = 10;
const int backwardPin = 11;
const int forwardPin = 12;
const int sensorVal = A0;

ClotheslineControl clothesline(ledSignal, backwardPin, forwardPin, sensorVal);

void setup() {
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(ledSignal, OUTPUT);

  delay(1000);

  Serial.begin(9600);
}

void loop() {
  int value = analogRead(sensorVal);
  Serial.print("Value: ");
  Serial.println(value);
  delay(100);

  clothesline.execute(value);
}