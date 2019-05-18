#include "laser.h"

Laser::Laser(void){
  pinMode(laser,OUTPUT);
  pinMode(lightsensor, INPUT);
}

bool Laser::laser_detect(int threshold){
  // if robot detects reflective surface, we plot green dots at the location
  // Right now we're just plotting green dots at random locations
  int onVal = 0;
  int offVal = 0;
  digitalWrite(laser, HIGH); 
  onVal = analogRead(lightsensor);
  delay(10);
  digitalWrite(laser, LOW); 
  offVal = analogRead(lightsensor);
  delay(10);
  Serial.println(offVal-onVal);
  if ((offVal-onVal) > threshold){
    return true;
  }
  else{
    return false;
  }
}
