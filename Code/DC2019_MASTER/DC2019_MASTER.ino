#include "BluetoothSerial.h"
#include "laser.h"
#include "ultrasense.h"
#include "motor.h"
#include "gripper.h"
#include <stdio.h>
#include <math.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

BluetoothSerial SerialBT; //instantiate bluetooth serial
Laser laser; // instantiate laser detector
Ultrasense usensor;
Motor motor;
Gripper gripper;

// Needed for vive
char message1[50];
int m1 = 0;
float xpos1 = 0, ypos1 = 0, xpos2 = 0, ypos2 = 0; 
double xcenter = 0, ycenter = 0, botAngle = 0;
int orientation;

// for vive calculation
//    8----76----5
//vive|          |
//    1----23----4

// ***********side is either 1278 or 3456***************
int side = 1278;

double corner1[] = {2.2, -4.1};
double corner2[] = {13.4, -2.2};
double corner3[] = {2.56, -2.6};
double corner4[] = {13.5, 1.8};
double corner5[] = {2.6, 2.7};
double corner6[] = {13.4, -2.2};
double corner7[] = {2.6, 2.7};
double corner8[] = {13.4, -2.2};


Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  attachInterrupt(digitalPinToInterrupt(motor.M1Encoder), ISRcountM1, RISING); // Every time encoder pulse rises, count the number of ticks
  attachInterrupt(digitalPinToInterrupt(motor.M2Encoder), ISRcountM2, RISING); // Every time encoder pulse rises, count the number of ticks 
  Serial.begin(115200);
  SerialBT.begin("HunterLuckless"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial2.begin(9600,SERIAL_8N1, 16, 17); // for teensy. Tx1 = pin 17, Rx1 = pin 16
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);
}

void loop() {
  char p;
  getOrientation();
  scan();
  checkVive();
  calcPosition();
  
  //Serial.print(xpos1);
  //Serial.print(" ");
  //Serial.println(ypos1);
  
  // SerialBT.println(vive calculation);
//  /************SEND DATA AND LISTEN TO BLUETOOTH ***************/
  if (SerialBT.available()) {
     p = SerialBT.read();

    if (p == 'w'){
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

    else if (p == '9'){
      Serial.print('9');
      bool grabbed = gripper.closeGripper();
      if (grabbed){
        SerialBT.println('k');
      }
    }
    else if (p == '8'){
      Serial.print('8');
      SerialBT.println('l');
      gripper.openGripper(180);
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
  float xpos = 0, ypos = 0;
  for (int i=0; i<5; i++){
    distance = distance + usensor.distance_detect();
  }
  distance = distance/5;
  //Serial.println(distance);

  if ((distance < 12) and (distance > 4.5)){
    
    laserThreshold = -900;
    if (laser.laser_detect(laserThreshold)){
      SerialBT.print("g ");
      //Serial.print("g ");
    } else{
      SerialBT.print("r ");
      //Serial.print("r ");
    }
    xpos = xcenter +(distance*8+64)*sin(-orientation*3.141/180);
    ypos = ycenter +(distance*8+64)*cos((180-orientation)*3.141/180);
    SerialBT.print(int(xpos));
    SerialBT.print(" ");
    SerialBT.println(int(ypos));
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

void calcPosition(){
  if (side == 1278){
    xcenter = 12*8*((xpos1+xpos2)/2 - corner1[0]);
    ycenter = 12*8*((ypos1+ypos2)/2 - corner1[1]);
  }
  else{
    xcenter = 12*8*((xpos1+xpos2)/2 - corner5[0]);
    ycenter = 12*8*((ypos1+ypos2)/2 - corner5[1]);
  }

  SerialBT.print("p ");
  SerialBT.print(int(xcenter));
  SerialBT.print(" ");
  SerialBT.println(int(ycenter));

  Serial.print("p ");
  Serial.print(int(xcenter));
  Serial.print(" ");
  Serial.println(int(ycenter));

}

void getOrientation(){
   /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  orientation = event.orientation.x;
  
  /* Display the floating point data */

  SerialBT.print("i ");
  SerialBT.println(orientation);
  
  delay(100);
}

