const int M1PWM = 15; // Motor 1 PWM (speed)
const int M1DIR = 32; // Motor 1 direction 
const int M2PWM = 4; // Motor 2 PWM (speed)
const int M2DIR = 5; // Motor 2 direction 

const int M1A = 26;
const int M1B = 25;
const int PWM1channel = 0;
const int PWM2channel = 1;



void setup() {
  ledcSetup(PWM1channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M1PWM,PWM1channel); // pin, pwm channel
  pinMode(M1DIR, OUTPUT);
  digitalWrite(M1DIR, LOW);

  ledcSetup(PWM2channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M2PWM,PWM2channel); // pin, pwm channel
  pinMode(M2DIR, OUTPUT);
  digitalWrite(M1DIR, LOW);

  pinMode(M1A, INPUT);
  pinMode(M1B, INPUT);

  Serial.begin(115200);

}

void loop() {
  Serial.println("forward");
  forward(255);
  delay(3000);


  Serial.println("backward");
  backward(255);
  delay(3000);

}

// Go forward
// this function takes parameter "speed" from 0 - 255
void forward(int spd) {
  digitalWrite(M1DIR,HIGH);
  ledcWrite(PWM1channel,spd);
  digitalWrite(M2DIR,LOW);
  ledcWrite(PWM2channel,spd);
  delay(10);
}

// Go backward
// this function takes parameter "speed" from 0 - 255
void backward(int spd) {
  digitalWrite(M1DIR,LOW);
  ledcWrite(PWM1channel,spd);
  digitalWrite(M2DIR,HIGH);
  ledcWrite(PWM2channel,spd);
}

// turn left
// this function takes parameter "speed" from 0 - 255 
void turnLeft(int spd){ 
  digitalWrite(M1DIR,HIGH);
  ledcWrite(PWM1channel,spd);
  digitalWrite(M2DIR,HIGH);
  ledcWrite(PWM2channel,spd);
}

// turn right
// this function takes parameter "speed" from 0 - 255
void turnRight(int spd){
  digitalWrite(M1DIR,LOW);
  ledcWrite(PWM1channel,spd);
  digitalWrite(M2DIR,LOW);
  ledcWrite(PWM2channel,spd);
}

// stop
void stopMotor() {
  ledcWrite(PWM1channel,0);
  ledcWrite(PWM1channel,0);
}
