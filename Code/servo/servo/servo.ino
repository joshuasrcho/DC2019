
#include <Servo.h> // Include the Servo library 

const int servo = 14; // Declare the Servo pin 

Servo Claw; // Create a servo object, Claw 

int pos = 0;    // variable to store the servo position

void setup() {
  Claw.attach(servo); // attach the servo to the used pin number 
  Serial.begin(9600);
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
}

// This function makes the robot grab cube
void closeClaw(){
  for(int i=0;i<130;i++){
    Claw.write(180-i); // Make servo go to 169 degrees 
    delay(5);
  }
  delay(1000);
}

