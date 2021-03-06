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
int en1_pin = 9;
//second motor
int q3_pin = 5;
int q4_pin = 6;
int en2_pin = 8;

//input pins
int go_pin = 51;
int rev_pin = 49;
int stop_pin = 31;
int l_pin = 47;
int r_pin = 45;
int spin_pin = 43;


int motor1_speed = 255;
int motor2_speed = 255;

enum State_enum{BRAKE, SPIN, FWD, REV, LEFT, RIGHT};
uint8_t state = BRAKE;

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

  //Input pins
  pinMode(go_pin, INPUT_PULLUP);
  pinMode(rev_pin, INPUT_PULLUP);
  pinMode(stop_pin, INPUT_PULLUP);
  pinMode(spin_pin, INPUT_PULLUP);
  pinMode(l_pin, INPUT_PULLUP);
  pinMode(r_pin, INPUT_PULLUP);
}

void loop() {

  /*
  clockwise();
  delay(2000);

  brake();
  delay(500);

  ccw();
  delay(2000);

  brake();
  delay(500);

  right_turn();
  delay(2000);

  brake();
  delay(500);

  left_turn();
  delay(2000);

  brake();
  delay(500);

  full_spin();
  delay(2000);

  brake();
  delay(500); */

  /*if(digitalRead(go_pin)){
    clockwise();
  } else{
    brake();
  }*/

  state_machine();
  delay(30);
  
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
