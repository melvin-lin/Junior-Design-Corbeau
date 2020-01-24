/*
 * AnalogInput
 * Controls state machine 
 * modified 22 Jan 2020
 * Melissa Rowland
 * Corbeau
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

int pot1Pin = A0;    // select the input pin for the potentiometer
int pot1Value = 0;
int pot2Pin = A2;
int pot2Value = 0;
int redLED = 2;    // select the pin for the red LED
int greenLED = 3; //select pin for green LED
int blueLED = 40; //select pin for blue LED
int switch8 = 52;
int switch7 = 50;
int switch3 = 48;
int switch2 = 46;
int switch1 = 44;
int brightness = 0;
int fadeAmt = 5;

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
}

void blinkBlue(int num){
  for(int i = 0; i < num; i++){
    digitalWrite(blueLED, HIGH);
    delay(300);
    digitalWrite(blueLED, LOW);
    delay(300);
  }
}

void blinkRed(int num, int potValue){
  for(int i = 0; i < num; i++){
    digitalWrite(redLED, HIGH);
    delay(potValue / 2);
    digitalWrite(redLED, LOW);
    delay(potValue / 2);
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
  pot2Value = analogRead(pot2Pin);
  pot2Value = pot2Value;
  if(pot2Value < 0){
    pot2Value = 0;
  } else if(pot2Value > 255){
    pot2Value = 255;
  }
  analogWrite(greenLED, pot2Value);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
}

void OFF_STATUS(){
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  
}

void RUN_STATUS(){
  pot1Value = analogRead(pot1Pin);
  
  //fade in led
  for(int fadeValue = 0; fadeValue <= 255; fadeValue +=5){
    analogWrite(redLED, fadeValue);
    delay(pot1Value);
  }
  
  blinkRed(4, pot1Value);
  
  //fade out led
  for(int fadeValue = 255; fadeValue >= 0; fadeValue -=5){
    analogWrite(redLED, fadeValue);
    delay(pot1Value);
  }

}

void DIAG_STATUS(){
  
  
}

void fail(){
  if(digitalRead(switch1)){
    blinkBlue(1);
  }
  else if(digitalRead(switch2)){
    blinkBlue(2);
  }
  else if(digitalRead(switch3)){
    blinkBlue(3);
  }
  delay(1500);
}
 
