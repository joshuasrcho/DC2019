const int M1PWM = 3; // Motor 1 PWM (speed)
const int M1DIR = 2; // Motor 1 direction 
const int M2PWM = 4; // Motor 2 PWM (speed)
const int M2DIR = 5; // Motor 2 direction 

void setup() {
  pinMode(M1DIR, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(M2PWM, OUTPUT);

}

void loop() {

  forward(255);
  delay(3000);
  forward(100);
  delay(3000);
  turnLeft(75);
  delay(3000);
  turnRight(75);
  delay(3000);
  backward(100);
  delay(3000);
  stopMotor();
  delay(3000);

}

// Go forward
// this function takes parameter "speed" from 0 - 255
void forward(int spd) {
  digitalWrite(M1DIR,HIGH);
  analogWrite(M1PWM,spd);
  digitalWrite(M2DIR,LOW);
  analogWrite(M2PWM,spd);
  delay(10);
}

// Go backward
// this function takes parameter "speed" from 0 - 255
void backward(int spd) {
  digitalWrite(M1DIR,LOW);
  analogWrite(M1PWM,spd);
  digitalWrite(M2DIR,HIGH);
  analogWrite(M2PWM,spd);
}

// turn left
// this function takes parameter "speed" from 0 - 255 
void turnLeft(int spd){ 
  digitalWrite(M1DIR,HIGH);
  analogWrite(M1PWM,spd);
  digitalWrite(M2DIR,HIGH);
  analogWrite(M2PWM,spd);
}

// turn right
// this function takes parameter "speed" from 0 - 255
void turnRight(int spd){
  digitalWrite(M1DIR,LOW);
  analogWrite(M1PWM,spd);
  digitalWrite(M2DIR,LOW);
  analogWrite(M2PWM,spd);
}

// stop
void stopMotor() {
  analogWrite(M1PWM,0);
  analogWrite(M2PWM,0);
}




