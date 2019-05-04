const int M1PWM = 15; // Motor 1 PWM (speed)
const int M1DIR = 32; // Motor 1 direction 
const int M2PWM = 26; // Motor 2 PWM (speed)
const int M2DIR = 25; // Motor 2 direction 

// Motor 1 encoder
const int M1A = 4;
const int M1B = 36;

// Motor 2 encoder

// Set up PWM channels
const int PWM1channel = 0;
const int PWM2channel = 1;

int counter = 0;
int currStateA;
int prevStateA;
String encdir = "";



void setup() {
  // Motor 1 setup
  ledcSetup(PWM1channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M1PWM,PWM1channel); // pin, pwm channel
  pinMode(M1DIR, OUTPUT);
  pinMode(M1A, INPUT);
  pinMode(M1B, INPUT);
  digitalWrite(M1DIR, LOW);
  prevStateA = digitalRead(M1A);
  

  ledcSetup(PWM2channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(M2PWM,PWM2channel); // pin, pwm channel
  pinMode(M2DIR, OUTPUT);
  digitalWrite(M2DIR, LOW);

  Serial.begin(115200);

  

}

void loop() {
  // Read the current state of M1A
  currStateA = digitalRead(M1A);

  // If the previous and the current state of M1A are different, then a pulse has occurred
  if (currStateA != prevStateA){
    if (digitalRead(M1B) != currStateA){
      counter --;
      encdir = "CCW";
    } else{
      counter ++;
      encdir = "CW";
    }
    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" counter: ");
    Serial.println(counter);
    prevStateA = currStateA;
  }
}

void M1EncoderUpdate(){
  
}

// Go forward
// this function takes parameter "speed" from 0 - 255
void forward(int spd) {
  digitalWrite(M1DIR,LOW);
  digitalWrite(M2DIR,HIGH);
  ledcWrite(PWM1channel,spd);
  ledcWrite(PWM2channel,spd);
}

// Go backward
// this function takes parameter "speed" from 0 - 255
void backward(int spd) {
  digitalWrite(M1DIR,HIGH);
  digitalWrite(M2DIR,LOW);
  ledcWrite(PWM1channel,spd);
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
  ledcWrite(PWM2channel,0);
}
