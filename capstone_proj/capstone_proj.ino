const int PIR_PIN = 34;
int motion_status = 0; // current pin reading
int pir_state = 0; // PIR state change

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  motionStatus = digitalRead(PIR_PIN);
  if (motion_status == HIGH) {

    if (pir_state == LOW) {
      
    }
  })
}
