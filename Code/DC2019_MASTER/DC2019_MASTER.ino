#include "BluetoothSerial.h"
#include <stdio.h>
#include <math.h>

BluetoothSerial SerialBT;

/******Laser**********/
const int laser = 12;
const int lightsensor = A2;
/***ultrasonic sensor***/
const int trigPin = 27;
const int echoPin = 33;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("HunterLuckless"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(laser,OUTPUT);
  pinMode(lightsensor, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  digitalWrite(13,LOW);
}

String readBTline(){ 
  // This function reads a integer value sent from laptop. It's like readline function.
  // Each string sent from laptop must end with '\n'
  String instring="";
  while (!SerialBT.available()){;}
  while (SerialBT.available()){
        char received = SerialBT.read();
        if (received == '\n'){
          return instring;
        }
        instring += received;
  }    
}

bool laser_detect(){
  /******* LASER *********/
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
    //SerialBT.print("o ");
    ///SerialBT.print(random(1,500)); 
    //SerialBT.print(" ");
    //SerialBT.println(random(1,500));
    return true;
  }
  else{
    Serial.println("not detected");
    return false;
  }
}

void distance_detect(){
  long duration = 0;
  long distance;
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
  if (distance < 20){
    Serial.print("Distance: ");
    Serial.println(distance);
    if (laser_detect()){
      SerialBT.print("o ");
      Serial.println("sending o");
    } else{
      Serial.println("sending r");
      SerialBT.print("r ");
    }
    SerialBT.print(250); 
    SerialBT.print(" ");
    SerialBT.println(distance*20);
  }
}


void loop() {
  char c = 0;
  int an = 0;
  distance_detect();

 
  
  /************SEND DATA AND LISTEN TO BLUETOOTH ***************/
  if (SerialBT.available()) {
    c = SerialBT.read();
    if(c == 'o'){ // next two numbers received are x and y coordinate of target
      String xpos = readBTline();
      String ypos = readBTline();
      
      Serial.print('o');
      Serial.print(' ');
      Serial.print(xpos);
      Serial.print(' ');
      Serial.println(ypos);
      
      digitalWrite(12,HIGH);
      
      SerialBT.print("o ");
      SerialBT.print(xpos);
      SerialBT.print(" ");
      SerialBT.println(ypos);
    }
    else if (c == 'p'){
      digitalWrite(12,LOW);
    }
    else if (c == 'a'){
      an = analogRead(A2);
      SerialBT.print("a ");
      SerialBT.println(an);
    }
    else if (c == 'x'){
      ;
    }
    else if (c == 'c'){
      SerialBT.println("c 1");
    }
  }
  delay(20);
  /****************************************************/
}

