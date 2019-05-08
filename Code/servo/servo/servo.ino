
#include <Servo.h> // Include the Servo library 

const int servo = 15; // Declare the Servo pin 
const int pb1= 13;
const int pb2= 39;

Servo Claw; // Create a servo object, Claw 

void setup() {
  Claw.attach(servo); // attach the servo to the used pin number 
  Serial.begin(115200);
  pinMode (pb1, INPUT);
  pinMode (pb2, INPUT);
}

void loop() {
  openClaw();
  closeClaw();
}

// This function makes the robot open its claw
void openClaw(){
  Serial.println("opening..");
  for(int i=Claw.read(); i<180; i++){
    Claw.write(i); // Make servo go to 180 degrees 
    delay(5);
  }
  delay(1000);
}

// This function makes the robot grab cube
bool closeClaw(){
  Serial.println("closing..");
  int pbval1; 
  int pbval2;
  for (int i=180; i>0; i--){
    pbval1=digitalRead(pb1);
    pbval2=digitalRead(pb2);
    Claw.write(i);
    delay(5);
    if (pbval1 and pbval2){
      Serial.println("Grabbed something!");
      return true;
    }else if (Claw.read() == 30) {
      Serial.println("didn't grab anything");
      return false;
    }
  }
  delay(1000);
}
