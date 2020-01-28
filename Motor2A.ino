/*
 *  Motor
 *  Phase 2A
 *  Corbeau Team
 *  Junior Design
 *  1/28/20
 */

int onSwitch = 1;
int motorGate = 4;
int inputPin = A0;
int motorValue;

void setup() {
  pinMode(motorGate, OUTPUT);
  pinMode(onSwitch, INPUT);
  pinMode(inputPin, INPUT);

}

void loop() {
  motorValue = 255;
  
  if(digitalRead(onSwitch)){
    analogWrite(motorGate, motorValue);
  }

}
