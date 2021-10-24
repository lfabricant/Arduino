/* Write a function at the bottom called 
 *  void motorRun(int speedl, int speedr)
 *  function takes in two numbers between -255 and 255
 *  if both numbers +, car moves forward
 *  if both numbers -, car moves backward
 *  if the first - and second +, turn left
 *  if first + and second -, turn right
 */

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT 4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT 6

void setup() {
  pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
  pinMode(PIN_DIRECTION_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
}

void loop() {
  // Move forward
  motorRun(200, 200);
  delay(1000);

  // Move backward
  motorRun(-200, -200);
  delay(1000);
  
  // Turn left
  motorRun(-200, 200);
  delay(1000);
  
  // Turn right
  motorRun(200, -200);
  delay(1000); 
}

void motorRun(int speedl, int speedr){
  boolean model = 0; // LOW
  boolean moder = 1; // HIGH
  speedl = abs(speedl);
  speedr = abs(speedr);
  if(speedl < 0){
    model = 1; // HIGH
  }
  if (speedr < 0){
    moder = 0; // LOW
  }
  digitalWrite(PIN_DIRECTION_LEFT, model); // This is FORWARD on the LEFT side
  analogWrite(PIN_MOTOR_PWM_LEFT, speedl);
  digitalWrite(PIN_DIRECTION_RIGHT, moder); // This is FORWARD on the RIGHT side
  analogWrite(PIN_MOTOR_PWM_RIGHT, speedr);
}

/*
void motorRun(int speedl, int speedr){
  if (speedl >= 0 && speedr >= 0){ 
    // move forward
    digitalWrite(PIN_DIRECTION_LEFT, LOW); // This is FORWARD on the LEFT side
    analogWrite(PIN_MOTOR_PWM_LEFT, speedl);
    digitalWrite(PIN_DIRECTION_RIGHT, HIGH); // This is FORWARD on the RIGHT side
    analogWrite(PIN_MOTOR_PWM_RIGHT, speedr);
    
  } else if (speedl < 0 && speedr < 0){
    // move backward
    digitalWrite(PIN_DIRECTION_LEFT, HIGH); // This is REVERSE on the LEFT side
    analogWrite(PIN_MOTOR_PWM_LEFT, -speedl);
    digitalWrite(PIN_DIRECTION_RIGHT, LOW); // This is REVERSE on the RIGHT side
    analogWrite(PIN_MOTOR_PWM_RIGHT, -speedr);
    
  } else if (speedl < 0 && speedr > 0){
    // turn left
    digitalWrite(PIN_DIRECTION_LEFT, HIGH); // This is REVERSE on the LEFT side
    analogWrite(PIN_MOTOR_PWM_LEFT, -speedl);
    digitalWrite(PIN_DIRECTION_RIGHT, HIGH); // This is FORWARD on the RIGHT side
    analogWrite(PIN_MOTOR_PWM_RIGHT, speedr);
    
  } else if (speedl > 0 && speedr < 0){
    // turn right
    digitalWrite(PIN_DIRECTION_LEFT, LOW); // This is FORWARD on the LEFT side
    analogWrite(PIN_MOTOR_PWM_LEFT, speedl);
    digitalWrite(PIN_DIRECTION_RIGHT, LOW); // This is REVERSE on the RIGHT side
    analogWrite(PIN_MOTOR_PWM_RIGHT, -speedr);
  } 
} */
