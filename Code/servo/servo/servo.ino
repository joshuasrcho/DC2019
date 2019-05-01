
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
  Claw.write(180); // Make servo go to 169 degrees 
  delay(1000); // wait 1 second
}

// This function makes the robot grab cube
void closeClaw(){
  Claw.write(0);
  delay(1000);
}

