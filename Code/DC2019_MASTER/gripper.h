#ifndef GRIPPER_H
#define GRIPPER_H

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Servo.h>

class Gripper{
  public:
    Gripper(void);
    void openGripper(int angle);
    bool closeGripper(void);
    
  private: 
    const int servo = 15; // Declare the Servo pin 
    const int pb1= 13;
    const int pb2= 39; 
    Servo Claw; // Create a servo object, Claw
};


#endif
