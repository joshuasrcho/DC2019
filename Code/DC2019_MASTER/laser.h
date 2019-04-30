#ifndef LASER_H
#define LASER_H

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Laser {
  public:
    Laser(void);
    bool laser_detect(void);
  private: 
    const int laser = 12;
    const int lightsensor = A2;
};

#endif

