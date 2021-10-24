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
  // LEFT motors rotate in REVERSE direction
  digitalWrite(PIN_DIRECTION_LEFT, HIGH); // This is REVERSE on the LEFT side
  analogWrite(PIN_MOTOR_PWM_LEFT, 100); // 100 is pwm signal (between 0 and 255)
  delay(1000);
  analogWrite(PIN_MOTOR_PWM_LEFT, 0); // stop the motor with a 0 PWM signal
  delay(1000);

  // LEFT motors rotate in FORWARD direction
  digitalWrite(PIN_DIRECTION_LEFT, LOW); // This is FORWARD on the LEFT side
  analogWrite(PIN_MOTOR_PWM_LEFT, 255); // 100 is pwm signal (between 0 and 255)
  delay(1000);
  analogWrite(PIN_MOTOR_PWM_LEFT, 0); // stop the motor with a 0 PWM signal
  delay(1000);

  // RIGHT motors rotate in FORWARD direction
  digitalWrite(PIN_DIRECTION_RIGHT, HIGH); // This is FORWARD on the RIGHT side
  analogWrite(PIN_MOTOR_PWM_RIGHT, 100); // 100 is pwm signal (between 0 and 255)
  delay(1000);
  analogWrite(PIN_MOTOR_PWM_RIGHT, 0); // stop the motor with a 0 PWM signal
  delay(1000);
  
  // RIGHT motors rotate in REVERSE direction
  digitalWrite(PIN_DIRECTION_RIGHT, LOW); // This is REVERSE on the RIGHT side
  analogWrite(PIN_MOTOR_PWM_RIGHT, 255); // 100 is pwm signal (between 0 and 255)
  delay(1000);
  analogWrite(PIN_MOTOR_PWM_RIGHT, 0); // stop the motor with a 0 PWM signal
  delay(1000);
}
