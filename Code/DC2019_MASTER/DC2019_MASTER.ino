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

void loop() {
  char c = 0;
  int an = 0;
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
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
      
      SerialBT.print('o');
      SerialBT.print(' ');
      SerialBT.print(xpos);
      SerialBT.print(' ');
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

