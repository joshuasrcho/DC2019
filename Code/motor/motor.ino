const int M1PWM = 15; // Motor 1 PWM (speed)
const int M1DIR = 32; // Motor 1 direction
const int M1Encoder = 4; // Motor 1 encoder 
const int M2PWM = 26; // Motor 2 PWM (speed)
const int M2DIR = 25; // Motor 2 direction 
const int M2Encoder = 36; // Motor 2 encoder

// Set up PWM channels
const int PWM1channel = 0;
const int PWM2channel = 1;

volatile int M1EncoderCount = 0;
volatile int M2EncoderCount = 0;

void setup() {
  // Motor 1 setup
  ledcSetup(PWM1channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M1PWM,PWM1channel); // pin, pwm channel
  pinMode(M1DIR, OUTPUT);
  pinMode(M1Encoder, INPUT);
  digitalWrite(M1DIR, LOW);
  attachInterrupt(digitalPinToInterrupt(M1Encoder), countM1, RISING);
  
  // Motor 2 setup
  ledcSetup(PWM2channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M2PWM,PWM2channel); // pin, pwm channel
  pinMode(M2DIR, OUTPUT);
  pinMode(M2Encoder, INPUT);
  digitalWrite(M2DIR, LOW);
  attachInterrupt(digitalPinToInterrupt(M2Encoder), countM2, RISING);
  Serial.begin(115200);

  

}

void loop() {
  forward(50,2000);
  delay(2000);
  backward(50,2000);
  delay(2000);
}

void countM1(){
  M1EncoderCount++;
}

void countM2(){
  M2EncoderCount++;
}

// Go forward
// this function takes parameter count
void forward(int PWM, int count) {
  digitalWrite(M1DIR,LOW);
  digitalWrite(M2DIR,HIGH);
  M1EncoderCount = 0;
  M2EncoderCount = 0;
  int totalCount = 0;
  int masterPWM = PWM;
  int slavePWM = PWM;
  int error = 0;
  int kp = 15;
  while(totalCount < count){
    ledcWrite(PWM1channel, masterPWM);
    ledcWrite(PWM2channel, slavePWM);
    error = M1EncoderCount - M2EncoderCount;
    slavePWM += (error/kp);
    if (slavePWM > 255){
      slavePWM = 255;
    } else if (slavePWM < 0){
      slavePWM = 0;
    }
    totalCount += M1EncoderCount;
    M1EncoderCount = 0;
    M2EncoderCount = 0;
    delay(100);
  }
  stopMotor();
  Serial.print("totalCount: ");
  Serial.println(totalCount);
}

// Go backward
// this function takes parameter "speed" from 0 - 255
void backward(int PWM, int count) {
  digitalWrite(M1DIR,HIGH);
  digitalWrite(M2DIR,LOW);
  M1EncoderCount = 0;
  M2EncoderCount = 0;
  int totalCount = 0;
  int masterPWM = PWM;
  int slavePWM = PWM;
  int error = 0;
  int kp = 1;
  while(totalCount < count){
    ledcWrite(PWM1channel, masterPWM);
    ledcWrite(PWM2channel, slavePWM);
    error = M1EncoderCount - M2EncoderCount;
    slavePWM -= (error/kp);
    if (slavePWM > 255){
      slavePWM = 255;
    } else if (slavePWM < 0){
      slavePWM = 0;
    }
    totalCount += M1EncoderCount;
    M1EncoderCount = 0;
    M2EncoderCount = 0;
    delay(100);
  }
  stopMotor();
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

void stopMotor() {
  ledcWrite(PWM1channel,0);
  ledcWrite(PWM2channel,0);
}

