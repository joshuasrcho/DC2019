#include <stdio.h>
#include "BluetoothSerial.h"
#include <math.h>
// defines pins numbers
BluetoothSerial SerialBT;
const int trigPin = 27;
const int echoPin = 33;
// defines variables
long duration;
int distance;
int c=0;
void setup() 
{
SerialBT.begin("test1"); //Bluetooth device name
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
} 

void loop() 
{
  
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.0133858/2;

Serial.println(distance);

SerialBT.println(distance);
}
