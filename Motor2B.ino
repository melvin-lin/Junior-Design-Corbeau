/*
 * Design Phase 2B
 * Motion Control
 * Corbeau Team
 * Junior Design
 * 2/2/20
 * 
 * 
 */


bool q1 = false;
bool q2 = false;
int q1_pin = 2;
int q2_pin = 3;
int en = 1;
int motor_speed = 150;

void clockwise();
void ccw();
void free_run();
void brake();



void setup() {
  pinMode(q1_pin, OUTPUT);
  pinMode(q2_pin, OUTPUT);
  pinMode(en, OUTPUT);

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

void clockwise(){
  analogWrite(q2_pin, 0);
  analogWrite(q1_pin, motor_speed); 
}

void ccw(){
  analogWrite(q1_pin, 0);
  analogWrite(q2_pin, motor_speed);
}

void brake(){
  analogWrite(q1_pin, 0);
  analogWrite(q2_pin, 0);
}
