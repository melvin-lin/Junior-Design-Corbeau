/*
 * AnalogInput
 * 
 * Source Code from Arduino Website:
 * created by David Cuartielles
 * modified 30 Aug 2011
 * By Tom Igoe
 * 
 * modified 22 Jan 2020
 * Melissa Rowland
 * EE31 Junior Design
 */
enum State_enum {OFF, ON, RUN, DIAG};
uint8_t state = OFF;
void state_machine_run();
void ON_STATUS();
void OFF_STATUS();
void RUN_STATUS();
void DIAG_STATUS();
void fail();
void blink(int num);

int potPin = A0;    // select the input pin for the potentiometer
int redLED = 38;    // select the pin for the red LED
int greenLED = 36; //select pin for green LED
int blueLED = 40; //select pin for blue LED
int potValue = 0;  // variable to store the value coming from the sensor
int switch8 = 52;
int switch7 = 50;
int switch3 = 48;
int switch2 = 46;
int switch1 = 44;

void setup() {
  // declare the led pins as OUTPUT:
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  //declare pins for switches as input
  pinMode(switch8, INPUT_PULLUP);
  pinMode(switch7, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP); 
  pinMode(switch1, INPUT_PULLUP);
}

void loop() {
  state_machine_run();
  delay(30);
  /*
  if(digitalRead(switch8)){
    digitalWrite(greenLED, HIGH);
  }else{
    digitalWrite(greenLED, LOW);
  }
  if(digitalRead(switch7)){
    digitalWrite(redLED, HIGH);
  }else{
    digitalWrite(redLED, LOW);
  }
  if(digitalRead(switch3)){
    blink(3);
  }else{
    digitalWrite(blueLED, LOW);
  }*/



  /*
  // read the value from the sensor:
  potValue = analogRead(potPin);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(potValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(potValue);*/
}

void blink(int num){
  for(int i = 0; i < num; i++){
    digitalWrite(blueLED, HIGH);
    delay(300);
    digitalWrite(blueLED, LOW);
    delay(300);
  }
}

void state_machine_run() 
{
  switch(state)
  {
    case OFF:
      if(digitalRead(switch8)){
        ON_STATUS();
        state = ON;
      }
      break;
       
    case ON:
      if(not digitalRead(switch8)){
        OFF_STATUS();
        state = OFF;
      }
      else if(digitalRead(switch7)){
        DIAG_STATUS();
        state = DIAG;
      }
      
      break;
 
    case RUN:
     if(not digitalRead(switch8)){
        OFF_STATUS();
        state = OFF;
      }
      else if(not digitalRead(switch7)){ //enable is off
        ON_STATUS();
        state = ON;
      }
      break;
 
    case DIAG:
      if(not digitalRead(switch8)){
        OFF_STATUS();
        state = OFF;
      }
      else if(digitalRead(switch3) or digitalRead(switch2) or digitalRead(switch1)){
        fail();
        state = OFF;
      }
      else {
        RUN_STATUS();
        state = RUN; 
      }
      
      break;
  }
}

void ON_STATUS(){
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
}
void OFF_STATUS(){
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  
}
void RUN_STATUS(){
  digitalWrite(redLED, HIGH);
  
}
void DIAG_STATUS(){
  
  
}

void fail(){
  if(digitalRead(switch1)){
    blink(1);
  }
  else if(digitalRead(switch2)){
    blink(2);
  }
  else if(digitalRead(switch3)){
    blink(3);
  }
  delay(1500);
}
 
