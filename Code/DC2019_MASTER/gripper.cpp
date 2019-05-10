#include "gripper.h"

Gripper::Gripper(void){
  Claw.attach(servo); // attach the servo to the used pin number 
  pinMode (pb1, INPUT);
  pinMode (pb2, INPUT);
}

// This function makes the robot open its claw
void Gripper::openGripper(){
  Serial.println("opening..");
  for(int i=Claw.read(); i<180; i++){
    Claw.write(i); // Make servo go to 180 degrees 
    delay(5);
  }
}

// This function makes the robot grab cube
bool Gripper::closeGripper(){
  Serial.println("closing..");
  int pbval1; 
  int pbval2;
  for (int i=180; i>0; i--){
    pbval1=digitalRead(pb1);
    pbval2=digitalRead(pb2);
    Claw.write(i);
    delay(5);
    if (pbval1 and pbval2){
      Claw.write(i-2);
      return true;
    }else if (Claw.read() == 30) {
      return false;
    }
  }
}

