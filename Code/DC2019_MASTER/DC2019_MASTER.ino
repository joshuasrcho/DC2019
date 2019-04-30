#include "BluetoothSerial.h"
#include "laser.h"
#include "ultrasense.h"
#include <stdio.h>
#include <math.h>

BluetoothSerial SerialBT; //instantiate bluetooth serial
Laser laser; // instantiate laser detector
Ultrasense usensor;

/***ultrasonic sensor***/
const int trigPin = 27;
const int echoPin = 33;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("HunterLuckless"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  digitalWrite(13,LOW);
}



void loop() {
  char c = 0;
  long distance = 0;
  distance = usensor.distance_detect();
  if (distance < 20){
    Serial.print("Distance: ");
    Serial.println(distance);
    if (laser.laser_detect()){
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


