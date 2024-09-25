#include "myMotorController.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   8
#define CSN_PIN 7

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

struct Data_Package {
  byte m1;
  byte m2;
  byte m3;
  byte m4;
};
Data_Package data;

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

myMotorController mc1(18, 19, 3);
myMotorController mc2(16,17,9);
myMotorController mc3(2,4,5);
myMotorController mc4(14, 15, 10);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    Serial.println("NODATA");
  }else{
    Serial.println(data.m1);
  }
  // for (int i = 0; i < 256; i++){
  //   mc1.setSpeed(i);
  //   delay(10);
  // }
  updateMotors();
  // mc1.reverseDirection();
  // delay(1000);
  // mc1.runForwardInt(200);
  // delay(1000);
  // mc1.runBackwardInt(50);
  // delay(1000);
  // mc1.reverseDirection();
  // delay(1000);
  // mc1.setSpeed(255);
  // delay(1000);
  // mc1.setSpeed(0);
  // delay(2000);
}

void resetData() {
  data.m1=0;
  data.m2=0;
  data.m3=0;
  data.m4=0;
}

void updateMotors(){
  if (data.m1!=0){
    mc1.setSpeed(255);
    if (data.m1==1){
      mc1.runForward();
    }else if (data.m2==2){
      mc1.runBackward();
    }
  }else{
    mc1.setSpeed(0);
  }
  if (data.m2!=0){
    mc2.setSpeed(255);
    if (data.m2==1){
      mc2.runForward();
    }else if (data.m2==2){
      mc2.runBackward();
    }
  }else{
    mc2.setSpeed(0);
  }
  if (data.m3!=0){
    mc3.setSpeed(255);
    if (data.m1==1){
      mc3.runForward();
    }else if (data.m3==2){
      mc3.runBackward();
    }
  }else{
    mc3.setSpeed(0);
  }
  if (data.m4!=0){
      mc4.setSpeed(255);
    if (data.m4==1){
      mc4.runForward();
    }else if (data.m4==2){
      mc4.runBackward();
    }
  }else{
    mc4.setSpeed(0);
  }
}