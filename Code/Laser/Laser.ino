#include "BluetoothSerial.h"

const int laser = 12;
const int led = 13;
const int lightsensor = 27;

int onVal = 100;
int offVal = 0;

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("HunterLuckless"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(laser, OUTPUT);
  pinMode(lightsensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(laser, HIGH); 
  onVal = analogRead(A2);
  delay(50);
  digitalWrite(laser, LOW); 
  offVal = analogRead(A2);
  delay(50);
  Serial.print(onVal);
  Serial.println(offVal);
  Serial.println("HI");
  SerialBT.write(Serial.read());
  
  if ((offVal-onVal) > 50){
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
}
