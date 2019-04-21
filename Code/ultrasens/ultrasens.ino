#include <stdio.h>
//#include "BluetoothSerial.h"
#include <math.h>
// defines pins numbers
//BluetoothSerial SerialBT;
const int trigPin = 27;
const int echoPin = 33;
// defines variables

void setup() 
{
//SerialBT.begin("HunterLuckless"); //Bluetooth device name
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
} 

void loop() 
{
  distance_detect();
}

void distance_detect(){
  long duration = 0;
  int distance;
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
  // Prints the distance on the Serial Monitor
  if (distance < 50){
    Serial.print("Distance: ");
    Serial.println(distance);
  }
}

