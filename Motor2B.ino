/*
 * Design Phase 2B
 * Motion Control
 * Corbeau Team
 * Junior Design
 * 2/2/20
 * 
 * 
 */

//first motor
int q1_pin = 2;
int q2_pin = 3;
int en1_pin = ;
//second motor
int q3_pin = 5;
int q4_pin = 6;
int en2_pin = ;
//input pins
/*
int go_pin = ;
int rev_pin = ;
int stop_pin = ;
int l_pin = ;
int r_pin = ;
*/

int motor1_speed = 70;
int motor2_speed = 255;

enum State_enum{BRAKE, FREE, FWD, REV, LEFT, RIGHT};
uint8_t state = FREE;

void clockwise();
void ccw();
void free_run();
void brake();
void right_turn();
void left_turn();
void state_machine();

void motor1_cw();
void motor2_cw();
void motor1_ccw();
void motor2_ccw();



void setup() {
  pinMode(q1_pin, OUTPUT);
  pinMode(q2_pin, OUTPUT);
  pinMode(q3_pin, OUTPUT);
  pinMode(q4_pin, OUTPUT);
  pinMode(en1_pin, OUTPUT);
  pinMode(en2_pin, OUTPUT);

}

void loop() {
  digitalWrite(en, HIGH);

  clockwise();
  delay(3000);

  brake();
  delay(1000);

  ccw();
  delay(3000);

  brake();
  delay(1000);
}

void state_machine(){
  switch(state){
    case FREE:
      break;

    case BRAKE:
      brake();
      break;

    case FWD:
      clockwise();
      break;

    case REV:
      ccw();
      break;

    case LEFT:
      left_turn();
      break;

    case RIGHT:
      right_turn();
      break;
  }
}

void clockwise(){
  motor1_cw();
  motor2_cw();
}

void ccw(){
  motor1_ccw();
  motor2_ccw();
}

void brake(){
  analogWrite(q1_pin, 0);
  analogWrite(q2_pin, 0);
  analogWrite(q3_pin, 0);
  analogWrite(q4_pin, 0);
}

void left_turn(){
}

void right_turn(){
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
  digitalWrite(en1_pin, HIGH);
  analogWrite(q3_pin, 0);
  analogWrite(q4_pin, motor2_speed);
}

void motor1_free(){
  digitalWrite(en1_pin, LOW);
}

void motor2_free(){
  digitalWrite(en2_pin, LOW);
}
