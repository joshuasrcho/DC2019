#include "BluetoothSerial.h"
#include <stdio.h>
#include <math.h>

BluetoothSerial SerialBT;

int count = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("HunterLuckless"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(12,OUTPUT);
  digitalWrite(13,LOW);
}

String readParameter(){
//  char buf[50];
//  for (int i = 0; i<50; i++){
//    char val = SerialBT.read();
//    if (val == ' '){
//      break;
//    }
//    else{
//        buf[i] = val;
//    }
//  }
//  String str((char*)buf);
//  return str;
  String content = "";
  char character;

  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
  }

  if (content != "") {
    Serial.println(content);
  }
}

void loop() {
  char c = 0;
  int an = 0;
  String xpos = "";
  char character = 0;
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    c = SerialBT.read();
    if(c == 'o'){ // next two numbers received are x and y coordinate of target
      while(character != 32){
        character = SerialBT.read();
        xpos.concat(character);
      }
      int xposn = xpos.toInt();
      int ypos = 100;
      Serial.print("o ");
      Serial.print(xposn);
      Serial.print(" ");
      Serial.println(ypos);
      
      digitalWrite(12,HIGH);
      
      SerialBT.print("o ");
      SerialBT.print(xposn);
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
}

