// LED.h
#ifndef myMotorController_h
#define myMotorController_h

#include <Arduino.h>

class myMotorController {
  private:
    int state;
    int mPin1;
    int mPin2;
  public:
    myMotorController(int a, int b, int c);
    void runForward();
    void runBackward();
    int getState();
    void runForwardInt(int i);
    void runBackwardInt(int i);
    void reverseDirection();
    void setSpeed(int i);
    int mPinPWM;
};

#endif