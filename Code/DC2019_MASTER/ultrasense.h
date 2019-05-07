#ifndef ULTRASENSE_H
#define ULTRASENSE_H

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Ultrasense {
  public:
    Ultrasense(void);
    float distance_detect(void);
  private: 
    const int trigPin = 27;
    const int echoPin = 33;
};




#endif
