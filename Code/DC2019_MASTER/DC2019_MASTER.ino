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
Gripper gripper;

// Needed for vive
char message1[50];
int m1 = 0;
float xpos1 = 0, ypos1 = 0, xpos2 = 0, ypos2 = 0;



void setup() {
  attachInterrupt(digitalPinToInterrupt(motor.M1Encoder), ISRcountM1, RISING); // Every time encoder pulse rises, count the number of ticks
  attachInterrupt(digitalPinToInterrupt(motor.M2Encoder), ISRcountM2, RISING); // Every time encoder pulse rises, count the number of ticks 
  Serial.begin(115200);
  SerialBT.begin("HunterLuckless"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial2.begin(9600,SERIAL_8N1, 16, 17); // for teensy. Tx1 = pin 17, Rx1 = pin 16
}

void loop() {
  char p;
  scan();
  checkVive();

  Serial.print(xpos1);
  Serial.print(" ");
  Serial.println(ypos1);
//  /************SEND DATA AND LISTEN TO BLUETOOTH ***************/
  if (SerialBT.available()) {
     p = SerialBT.read();
    if(p == 'o'){ // next two numbers received are x and y coordinate of target
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
    else if (p == 'w'){
      Serial.print('w');
      motor.forward(10);
    }
    else if (p == 's'){
      Serial.print('s');
      motor.backward(10);
    }
    else if (p == 'd'){
      Serial.print('d');
      motor.turnRight(10);
    } 
    else if (p == 'a'){
      Serial.print('a');
      motor.turnLeft(10);
    }

    else if (p == '0'){
      Serial.print('0');
      SerialBT.println('l');
      gripper.openGripper();
    } 
    else if (p == '9'){
      Serial.print('9');
      bool grabbed = gripper.closeGripper();
      if (grabbed){
        SerialBT.println('k');
      }
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
  int laserThreshold;
  float distance = 0;
//  for (int i=0; i<5; i++){
//    distance = distance + usensor.distance_detect();
//  }
//  distance = distance/5;
  //Serial.println(distance);
  distance = 6;
  
  if ((distance < 12) and (distance > 4.5)){
    laserThreshold = -900;
    if (laser.laser_detect(laserThreshold)){
      SerialBT.print("g ");
      //Serial.print("g ");
    } else{
      SerialBT.print("r ");
      //Serial.print("r ");
    }
    //Serial.print(int(distance*8));
    //Serial.print(" ");
    //Serial.println(250);
    
    SerialBT.print(int(distance*8));
    SerialBT.print(" ");
    SerialBT.println(250);
  }
  
}


void checkVive(){
  char type = ' ';
  float val1 = 0, val2 = 0;
  
  while(Serial2.available()){
    message1[m1] = Serial2.read();
    if (message1[m1] == '\n'){
      sscanf(message1,"%c %f %f", &type, &val1, &val2);
      if (type == 'a'){
        xpos1 = val1;
        ypos1 = val2;
      }
      else if (type == 'b'){
        xpos2 = val1;
        ypos2 = val2;
      }
      m1 = 0;
      int iii;
      for(iii=0;iii<50;iii++){
        message1[iii] = 0;
      }
    }
    else {
      m1++;
    }
  }
}

