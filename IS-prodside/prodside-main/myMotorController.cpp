#include "myMotorController.h"

myMotorController::myMotorController(int pin1, int pin2, int pwm) {
  mPin1 = pin1;
  mPin2 = pin2;
  mPinPWM = pwm;
  state = 0;
  setSpeed(255);
}

void myMotorController::runForward() {
  digitalWrite(mPin1, HIGH);
  digitalWrite(mPin2, LOW);
  state = 1;
}

void myMotorController::runBackward() {
  digitalWrite(mPin1, LOW);
  digitalWrite(mPin2, HIGH);
  state = -1;
}

void myMotorController::setSpeed(int i){
  analogWrite(mPinPWM, i);
}

int myMotorController::getState(){
  return state;
}

void myMotorController::runForwardInt(int i) {
  digitalWrite(mPin1, HIGH);
  digitalWrite(mPin2, LOW);
  analogWrite(mPinPWM, i);
  state = 1;
}

void myMotorController::runBackwardInt(int i) {
  digitalWrite(mPin1, LOW);
  digitalWrite(mPin2, HIGH);
  analogWrite(mPinPWM, i);
  state = -1;
}

void myMotorController::reverseDirection() {
  if (state==1){
    runBackward();
  } else if (state==-1){
    runForward();
  }else{
    return;
  }
}