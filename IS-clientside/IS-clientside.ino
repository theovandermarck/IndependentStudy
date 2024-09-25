#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
const byte address[6] = "00001";

struct Data_Package {
  byte m1;
  byte m2;
  byte m3;
  byte m4;
};
int currentIndex = 0;
Data_Package data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  data.m1=0;
  data.m2=0;
  data.m3=0;
  data.m4=0;
}
char c = "-1";
void loop() {
  // put your main code here, to run repeatedly:
  radio.write(&data, sizeof(Data_Package));
  if ( Serial.available())
    {
      char ch = Serial.read();
      if (ch != '9'){
        c=ch;
        Serial.println(c);
        setPackage(currentIndex, c);
        currentIndex++;
      }else{
        currentIndex = 0;
        Serial.print("E!");
        Serial.println(data.m1);
      }
    }
    
}
void setPackage(int i, char d){
  Serial.print("F");
  Serial.println(d);
  byte value = d - '0';
  switch (i){
    case 0:
      data.m1 = value;
    case 1:
      data.m2 = value;
    case 2:
      data.m3 = value;
    case 3:
      data.m4 = value;
    default:
      break;
  }
}