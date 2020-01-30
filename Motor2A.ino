/*
 *  Motor
 *  Phase 2A
 *  Corbeau Team
 *  Junior Design
 *  1/28/20
 */

int onSwitch = 2;
int motorGate = 4;
int potPin = A0;
int motorValue = 0;
int potValue = 0;

void setup() {
  pinMode(motorGate, OUTPUT);
  pinMode(onSwitch, INPUT_PULLUP);
}

void loop() {
  potValue = analogRead(potPin);
  if (potValue < 0 ){
    potValue = 0;
  } else if (potValue > 255){
    potValue = 255;
  }
  analogWrite(motorGate, motorValue);
  
  if(digitalRead(onSwitch)){
    motorValue = potValue;
  } else{
    motorValue = 0;
  }

}
