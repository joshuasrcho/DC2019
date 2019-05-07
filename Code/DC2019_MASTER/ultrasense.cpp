#include "ultrasense.h"

Ultrasense::Ultrasense(void){
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

float Ultrasense::distance_detect(){
  long duration = 0;
  float distance;
  for (int i = 0; i<3; i++){
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = duration + pulseIn(echoPin, HIGH);
  }
    
  // Calculating the distance
  distance= duration*0.0133858/6;

  return distance;
  }
