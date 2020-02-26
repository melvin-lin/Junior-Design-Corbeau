/*
 * Design Phase 3A
 * Sensing
 * Corbeau Team
 * Junior Design
 * 2/17/20
 * 
 * 
 */

//Output Pins
//First motor
int q1_pin = 2;
int q2_pin = 3;
int en1_pin = 9;
//Second motor
int q3_pin = 5;
int q4_pin = 6;
int en2_pin = 8;
//LEDs
int red_led = 50;
int blue_led = 52;
int red_led_out = 48;
int blue_led_out = 46;
int yel_led_out = 23;
//Hall
int hall_sensor = A4;

//Input pins
int light_sensor = A5;
//Dipswitch pins
int go_pin = 51;
int rev_pin = 49;
int stop_pin = 31;
int l_pin = 47;
int r_pin = 45;
int spin_pin = 43;

//Integers
int motor1_speed = 100;
int motor2_speed = 100;
int red_value = 0;
int blue_value = 0;
int hall_value = 0;
float red_threshold = 2.5;
float blue_threshold = 2.5;
float hall_threshold = 4;
float red_voltage = 0;
float blue_voltage = 0;
float hall_voltage = 0;

//States
enum State_enum{BRAKE, SPIN, FWD, REV, LEFT, RIGHT};
uint8_t state = BRAKE;

//Functions
void clockwise();
void ccw();
void free_run();
void brake();
void right_turn();
void left_turn();
void state_machine();
void full_spin();
void motor1_cw();
void motor2_cw();
void motor1_ccw();
void motor2_ccw();

void setup() {
  //Output pins
  pinMode(q1_pin, OUTPUT);
  pinMode(q2_pin, OUTPUT);
  pinMode(q3_pin, OUTPUT);
  pinMode(q4_pin, OUTPUT);
  pinMode(en1_pin, OUTPUT);
  pinMode(en2_pin, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(red_led_out, OUTPUT);
  pinMode(blue_led_out, OUTPUT);
  pinMode(yel_led_out, OUTPUT);

  //Input pins
  pinMode(go_pin, INPUT_PULLUP);
  pinMode(rev_pin, INPUT_PULLUP);
  pinMode(stop_pin, INPUT_PULLUP);
  pinMode(spin_pin, INPUT_PULLUP);
  pinMode(l_pin, INPUT_PULLUP);
  pinMode(r_pin, INPUT_PULLUP);

}

void loop() {
  //shine red led, read input
  digitalWrite(red_led, HIGH);
  delay(100);
  red_value = analogRead(light_sensor);
  red_voltage = red_value * (5.0 / 1023);
  delay(100);
  digitalWrite(red_led, LOW);
  
  delay(250);

  //shine blue led, read input
  digitalWrite(blue_led, HIGH);
  delay(100);
  blue_value = analogRead(light_sensor);
  blue_voltage = blue_value * (5.0 / 1023);
  delay(100);
  digitalWrite(blue_led, LOW);

  delay(250);

  hall_value = analogRead(hall_sensor);
  hall_voltage = hall_value * (5.0 / 1023);
  
  //make decision, output what color it senses
  if(red_voltage > red_threshold){
    digitalWrite(red_led_out, HIGH);
  } else{
    digitalWrite(red_led_out, LOW);
  }
  if(blue_voltage > blue_threshold){
    digitalWrite(blue_led_out, HIGH);
  } else{
    digitalWrite(blue_led_out, LOW);
  }
  
  if(hall_voltage > hall_threshold){
    digitalWrite(yel_led_out, HIGH);
  } else{
    digitalWrite(yel_led_out, LOW);
  } 
}

void state_machine(){
  switch(state){
    
    case BRAKE:
      brake();
      if(digitalRead(go_pin)){
        state = FWD;
      }
      else if(digitalRead(rev_pin)){
        state = REV;
      }
      else if(digitalRead(l_pin)){
        state = LEFT;
      }
      else if(digitalRead(r_pin)){
        state = RIGHT;
      }
      else if(digitalRead(spin_pin)){
        state = SPIN;
      }
      break;

    case FWD:
      if(digitalRead(stop_pin)){
        state = BRAKE;
      } else if(digitalRead(go_pin)){
        clockwise();
      } else{
        state = BRAKE;
      }
      break;

    case REV:
      if(digitalRead(stop_pin)){
        state = BRAKE;
      } else if(digitalRead(rev_pin)){
        ccw();
      } else{
        state = BRAKE;
      }
      break;

    case LEFT:
      if(digitalRead(stop_pin)){
        state = BRAKE;
      } else if(digitalRead(l_pin)){
        left_turn();
      } else{
        state = BRAKE;
      }
      break;

    case RIGHT:
      if(digitalRead(stop_pin)){
        state = BRAKE;
      } else if(digitalRead(r_pin)){
        right_turn();
      } else{
        state = BRAKE;
      }
      break;

    case SPIN:
      if(digitalRead(stop_pin)){
        state = BRAKE;
      } else if(digitalRead(spin_pin)){
        full_spin();
      } else{
        state = BRAKE;
      }
      break;
  }
}

//Motion Control Functions

void clockwise(){
  motor1_cw();
  motor2_cw();
}

void ccw(){
  motor1_ccw();
  motor2_ccw();
}

void brake(){
  digitalWrite(en1_pin, HIGH);
  digitalWrite(en2_pin, HIGH);
  analogWrite(q1_pin, 0);
  analogWrite(q2_pin, 0);
  analogWrite(q3_pin, 0);
  analogWrite(q4_pin, 0);
}

void left_turn(){
  motor1_cw();
  motor2_free();
}

void right_turn(){
  motor1_free();
  motor2_cw();
}

void full_spin(){
  motor1_cw();
  motor2_ccw();
}

void motor1_cw(){
  //first motor
  digitalWrite(en1_pin, HIGH);
  analogWrite(q2_pin, 0);
  analogWrite(q1_pin, motor1_speed); 
}

void motor2_cw(){
  //second motor
  digitalWrite(en2_pin, HIGH);
  analogWrite(q4_pin, 0);
  analogWrite(q3_pin, motor2_speed); 
}

void motor1_ccw(){
  //first motor
  digitalWrite(en1_pin, HIGH);
  analogWrite(q1_pin, 0);
  analogWrite(q2_pin, motor1_speed);
}

void motor2_ccw(){
  digitalWrite(en2_pin, HIGH);
  analogWrite(q3_pin, 0);
  analogWrite(q4_pin, motor2_speed);
}

void motor1_free(){
  digitalWrite(en1_pin, LOW);
}

void motor2_free(){
  digitalWrite(en2_pin, LOW);
}
