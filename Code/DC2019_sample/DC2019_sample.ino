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

void loop() {
  char c = 0;
  int an = 0;
  int i;
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    c = SerialBT.read();
    if(c == 'o'){
      digitalWrite(12,HIGH);
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
      count = count + 1;
      for (i=0; i<100; i++){
        SerialBT.print("x ");
        SerialBT.print(i);
        SerialBT.print(" ");
        SerialBT.println(int(50*sin(2*3.14/50*i+count)));
      }
    }
    else if (c == 'c'){
      SerialBT.println("c 1");
    }
  }
  delay(20);
}

