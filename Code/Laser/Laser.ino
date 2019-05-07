#include "BluetoothSerial.h"

const int laser = 12;
const int led = 13;
const int lightsensor = A2;

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
  onVal = analogRead(lightsensor);
  delay(50);
  digitalWrite(laser, LOW); 
  offVal = analogRead(lightsensor);
  delay(50);
  Serial.println(offVal-onVal);
  if ((offVal-onVal) > 500){
    Serial.println("detected");
    SerialBT.print("detected ");
  }
}
