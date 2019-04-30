#include "laser.h"

Laser::Laser(void){
  pinMode(laser,OUTPUT);
  pinMode(lightsensor, INPUT);
}

bool Laser::laser_detect(void){
  // if robot detects reflective surface, we plot green dots at the location
  // Right now we're just plotting green dots at random locations
  int onVal = 0;
  int offVal = 0;
  digitalWrite(laser, HIGH); 
  onVal = analogRead(lightsensor);
  delay(50);
  digitalWrite(laser, LOW); 
  offVal = analogRead(lightsensor);
  delay(50);
  if ((offVal-onVal) > 50){
    Serial.println("detected!");
    return true;
  }
  else{
    Serial.println("not detected");
    return false;
  }
}
