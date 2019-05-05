
#include <Servo.h> // Include the Servo library 

const int servo = 14; // Declare the Servo pin 
const int pb1= 13;
const int pb2= 39;

Servo Claw; // Create a servo object, Claw 

int pos = 0;    // variable to store the servo position

void setup() {
  Claw.attach(servo); // attach the servo to the used pin number 
  Serial.begin(9600);
  pinMode (pb1, INPUT);
  pinMode (pb2, INPUT);
}

void loop() {
  openClaw();
  closeClaw();
}

// This function makes the robot grab cylinder
void openClaw(){
  for(int i=50;i<180;i++){
    Claw.write(i); // Make servo go to 169 degrees 
    delay(5);
  }
  delay(1000);
  Serial.println("open");
}

// This function makes the robot grab cube
void closeClaw(){
  Serial.println("close");
  int pbval1= LOW;
  int pbval2= LOW;
  int count=180;
  while (pbval1== LOW and pbval2==LOW){
    pbval1=digitalRead(pb1);
    pbval2=digitalRead(pb2);
    Claw.write(count); // Make servo go to 169 degrees 
    count--;
    delay(5);
    if (count==25) {
      break; 
    }
  }
  delay(1000);
  
}
