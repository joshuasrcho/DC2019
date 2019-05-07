#ifndef MOTOR_H
#define MOTOR_H

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Motor{
  public:
    Motor(void);
    void forward(int distance); // distance increments by 1/8 of a inch (1 means 0.125 inch, 8 means 1 inch)
    void backward(int distance); 
    void stopMotor();

    volatile int M1EncoderCount = 0;
    volatile int M2EncoderCount = 0;
    const int M1Encoder = 4; // Motor 1 encoder 
    const int M2Encoder = 36; // Motor 2 encoder
    
  private: 
    const int M1PWM = 14; // Motor 1 PWM (speed)
    const int M1DIR = 32; // Motor 1 direction
    const int M2PWM = 26; // Motor 2 PWM (speed)
    const int M2DIR = 25; // Motor 2 direction 
    // Set up PWM channels
    const int PWM1channel = 0;
    const int PWM2channel = 1;    
};


#endif
