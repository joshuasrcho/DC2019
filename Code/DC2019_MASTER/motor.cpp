#include "motor.h"


Motor::Motor(void){
  // Motor 1 setup
  ledcSetup(PWM1channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M1PWM,PWM1channel); // pin, pwm channel
  pinMode(M1DIR, OUTPUT); // Motor 1 direction
  pinMode(M1Encoder, INPUT); // Motor 1 encoder
  digitalWrite(M1DIR, LOW); // initial motor direction is LOW
  
  
  // Motor 2 setup
  ledcSetup(PWM2channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M2PWM,PWM2channel); // pin, pwm channel
  pinMode(M2DIR, OUTPUT); // Motor 2 direction
  pinMode(M2Encoder, INPUT); // Motor 2 encoder
  digitalWrite(M2DIR, LOW); // initial motor direction is LOW
  
}



// Go forward
// this function takes parameter distance. 1 means 0.125 inches. 8 means 1 inches
// PWM duty cycle is (50/255)*100 = 20 percent
// 400 counts per revolution. Wheel diameter is 2.5 inches. 
// count = (distance*400) / (8*2.5*3.14)
void Motor::forward(int distance){
  digitalWrite(M1DIR,LOW);
  digitalWrite(M2DIR,HIGH);
  M1EncoderCount = 0; // reset M1 encoder count to 0
  M2EncoderCount = 0; // reset M2 encoder count to 0
  int totalCount = 0; // totalCount keeps track of how far the robot has traveled
  // masterPWM is the reference PWM value and is assigned to PWMChannel1 or M1
  // slavePWM adjusts based on error to try to keep the robot straight
  int masterPWM = 75; // Default PWM duty cycle of 20%
  int slavePWM = 75; // Default PWM duty cycle of 20%
  int error = 0; // initialize error to 0
  int kp = 15; // kp is the proportional constant. 15 seems to work well.

  int count = (distance*400)/(8*2.5*3.14); // convert input distance to number of encoder counts 
  
  while(totalCount < count){ // go forward until robot reaches target encoder count. Repeat this loop at 10Hz
    ledcWrite(PWM1channel, masterPWM); // Always drive M1 with masterPWM
    ledcWrite(PWM2channel, slavePWM); // Always drive M2 with slavePWM
    error = M1EncoderCount - M2EncoderCount; // calculate error between two encoder counts
    slavePWM += (error/kp); // adjust slavePWM based on error

    // Saturate slavePWM so that 0 <= slavePWM <= 255
    if (slavePWM > 255){
      slavePWM = 255;
    } else if (slavePWM < 0){
      slavePWM = 0;
    }
   
    totalCount += M1EncoderCount; // update total encoder count
    M1EncoderCount = 0; // reset M1 and M2 encoder count to 0 so that error calculation starts fresh in the next loop
    M2EncoderCount = 0;
    delay(100);
  }
  stopMotor();
}


// Go backward
// this function takes parameter distance. 1 means 0.125 inches. 8 means 1 inches
// PWM duty cycle is (50/255)*100 = 20 percent
// 400 counts per revolution. Wheel diameter is 2.5 inches. 
// count = (distance*400) / (8*2.5*3.14)
void Motor::backward(int distance) {
  digitalWrite(M1DIR,HIGH); 
  digitalWrite(M2DIR,LOW); 
  M1EncoderCount = 0; // reset M1 encoder count to 0
  M2EncoderCount = 0; // reset M2 encoder count to 0
  int totalCount = 0; // totalCount keeps track of how far the robot has traveled
  // masterPWM is the reference PWM value and is assigned to PWMChannel1 or M1
  // slavePWM adjusts based on error to try to keep the robot straight
  int masterPWM = 75; // Default PWM duty cycle of 20%
  int slavePWM = 75; // Default PWM duty cycle of 20%
  int error = 0; // initialize error to 0
  int kp = 2; // kp is the proportional constant. 2 seems to work well.

  int count = (distance*400)/(8*2.5*3.14); // convert input distance to number of encoder counts 
  
  while(totalCount < count){ // go backward until robot reaches target encoder count. Repeat this loop at 10Hz
    ledcWrite(PWM1channel, masterPWM); // Always drive M1 with masterPWM
    ledcWrite(PWM2channel, slavePWM); // Always drive M2 with slavePWM
    error = M1EncoderCount - M2EncoderCount; // calculate error between two encoder counts
    slavePWM -= (error/kp); // adjust slavePWM based on error (note - because we're going backward)
    
    // Saturate slavePWM so that 0 <= slavePWM <= 255
    if (slavePWM > 255){
      slavePWM = 255;
    } else if (slavePWM < 0){
      slavePWM = 0;
    }
    
    totalCount += M1EncoderCount; // update total encoder count
    M1EncoderCount = 0; // reset M1 and M2 encoder count to 0 so that error calculation starts fresh in the next loop
    M2EncoderCount = 0;
    delay(100);
  }
  stopMotor();
}

void Motor::turnRight(int angle){
  int count = (angle*1100)/360;
  M1EncoderCount = 0;
  M2EncoderCount = 0;
  int masterPWM = 100; // Default PWM duty cycle of 29%
  int slavePWM = 100; // Default PWM duty cycle of 29%
  int error;
  int kp = 2;
  int totalCount = 0;
  digitalWrite(M1DIR,HIGH); 
  digitalWrite(M2DIR,HIGH);
  while (totalCount < count){
    ledcWrite(PWM1channel,masterPWM);
    ledcWrite(PWM2channel,slavePWM);
    error = M1EncoderCount - M2EncoderCount;
    slavePWM -= error / kp;
    if (slavePWM > 255){
      slavePWM = 255;
    } else if (slavePWM < 0){
      slavePWM = 0;
    }
    //Serial.print("error: ");
    //Serial.println(error);
    //Serial.println(slavePWM);
    totalCount += M1EncoderCount;
    M1EncoderCount = 0;
    M2EncoderCount = 0;
    delay(100);
  }
  stopMotor();
}

void Motor::turnLeft(int angle){
  int count = (angle*1100)/360;
  M1EncoderCount = 0;
  M2EncoderCount = 0;
  int masterPWM = 100; // Default PWM duty cycle of 29%
  int slavePWM = 100; // Default PWM duty cycle of 29%
  int error;
  int kp = 1;
  int totalCount = 0;
  digitalWrite(M1DIR,LOW); 
  digitalWrite(M2DIR,LOW);
  while (totalCount < count){
    ledcWrite(PWM1channel,masterPWM);
    ledcWrite(PWM2channel,slavePWM);
    error = M1EncoderCount - M2EncoderCount;
    slavePWM -= error / kp;
    if (slavePWM > 255){
      slavePWM = 255;
    } else if (slavePWM < 0){
      slavePWM = 0;
    }
    //Serial.print("error: ");
    //Serial.println(error);
    //Serial.println(slavePWM);
    totalCount += M1EncoderCount;
    M1EncoderCount = 0;
    M2EncoderCount = 0;
    delay(100);
  }
  stopMotor();
}









void Motor::stopMotor() {
  ledcWrite(PWM1channel,0);
  ledcWrite(PWM2channel,0);
}

