#include "BluetoothSerial.h"
#include "laser.h"
#include "ultrasense.h"
#include "motor.h"
#include "gripper.h"
#include <stdio.h>
#include <math.h>

BluetoothSerial SerialBT; //instantiate bluetooth serial
Laser laser; // instantiate laser detector
Ultrasense usensor;
Motor motor;
//Gripper gripper;



void setup() {
  attachInterrupt(digitalPinToInterrupt(motor.M1Encoder), ISRcountM1, RISING); // Every time encoder pulse rises, count the number of ticks
  attachInterrupt(digitalPinToInterrupt(motor.M2Encoder), ISRcountM2, RISING); // Every time encoder pulse rises, count the number of ticks 
  Serial.begin(115200);
  SerialBT.begin("HunterLuckless"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  
  motor.turnLeft(360);

  
//  /************SEND DATA AND LISTEN TO BLUETOOTH ***************/
  if (SerialBT.available()) {
    char c = SerialBT.read();
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

void ISRcountM1(){ // ISR
  motor.M1EncoderCount++; // Every time encoder pulse rises, count the number of ticks
                    // Each revolution has ~400 ticks
}

void ISRcountM2(){ // ISR
  motor.M2EncoderCount++; // Every time encoder pulse rises, count the number of ticks
                    // Each revolution has ~400 ticks
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

// scan using usensor and laser. if detected, send object coordinates and red/green over bluetooth
void scan(){
  char c = 0;
  int laserThreshold;
  float distance = 0;
  distance = usensor.distance_detect();
  if ((distance < 12) and (distance > 4.5)){
    laserThreshold = -900;
    if (laser.laser_detect(laserThreshold)){
      SerialBT.print("g ");
      Serial.print("g ");
    } else{
      SerialBT.print("r ");
      Serial.print("r ");
    }
    Serial.print(int(distance*8));
    Serial.print(" ");
    Serial.println(250);
    
    SerialBT.print(int(distance*8));
    SerialBT.print(" ");
    SerialBT.println(250);
  }
}


