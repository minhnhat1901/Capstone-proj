// #include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int PIR_PIN = 34;
// const int RX_PIN = 23;
// const int TX_PIN = 22;

bool pir_state = LOW; // PIR state change
int motion_status = LOW; // current pin reading
// int track = 1;

// SoftwareSerial fxSerial(RX_PIN, TX_PIN);
DFRobotDFPlayerMini fxPlayer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);

  pinMode(PIR_PIN, INPUT);

  Serial1.begin(9600);
  delay(200);

  // Serial.println("Initializing DFPlayer…");
  // if (!fxPlayer.begin(fxSerial)) {
  //   Serial.println("DFPlayer init failed! Check wiring and SD card.");
  // } else {
  //   Serial.println("DFPlayer ready.");
  // }
  
  // Serial.println();

  // pinMode(RX_PIN, INPUT);
  // pinMode(TX_PIN, OUTPUT);

  fxPlayer.begin(Serial1);
  
  // Can set from 0 - 30
  fxPlayer.volume(20);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  motion_status = digitalRead(PIR_PIN);

  if (motion_status == HIGH && pir_state == LOW) {
    Serial.println("Motion Detected");
    pir_state = HIGH;

    // Add below things want to activate
    Serial.println("Playing track 1...");
    fxPlayer.play(1);
    delay(2500);
  }
  if (motion_status == LOW && pir_state == HIGH) {
    Serial.println("Motion Ended");
    pir_state = LOW;

    // Add below things want to deactivate
    Serial.println("Playing track 2...");
    fxPlayer.play(2);
    delay(2200);
  }

  delay(50);
}
