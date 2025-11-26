const int ledSignal = 10;
const int backwardPin = 11;
const int forwardPin = 12;
const int sensorVal = A0;

const int delayTime = 500;
const int stopTime = 2000;

bool hasBroughtIn = false;
bool hasBroughtOut = false;

void speedControl(int speed1, int speed2) {
  analogWrite(forwardPin, speed1);
  analogWrite(backwardPin, speed2);
}

void stopMove() {
  digitalWrite(forwardPin, LOW);
  digitalWrite(backwardPin, LOW);
}

void bringoutMove() {
  digitalWrite(forwardPin, HIGH);
  digitalWrite(backwardPin, LOW);
}

void bringinMove() {
  digitalWrite(forwardPin, LOW);
  digitalWrite(backwardPin, HIGH);
}