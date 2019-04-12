

const int laser = 12;
const int led = 13;
const int lightsensor = 27;

int onVal;
int offVal;


void setup() {
  pinMode(laser, OUTPUT);
  pinMode(lightsensor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.println((offVal-onVal));
  digitalWrite(laser, HIGH); 
  onVal = analogRead(lightsensor);
  delay(50);
  digitalWrite(laser, LOW); 
  offVal = analogRead(lightsensor);
  delay(50);
  
  if ((offVal-onVal) > 50){
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
}
