#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

class ClotheslineControl {
  public:
    ClotheslineControl();
    ClotheslineControl(int ledPin, int backPin, int forePin, int sensorPin);
    void speedControl(int speed1, int speed2);
    void stopMove();
    void bringoutMove();
    void bringinMove();
    void execute(int value);

  private:
    const int DELAYTIME = 500;
    const int STOPTIME = 2000;
    bool hasBroughtIn;
    bool hasBroughtOut;

    int ledSignal;
    int backwardPin;
    int forwardPin;
    int sensorVal;
};

#endif