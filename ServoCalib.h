#include<Servo.h> 

// Create servo objects
Servo Servo_0;
Servo Servo_1;
Servo Servo_2;
Servo Servo_3;

void setup() {
  // put your setup code here, to run once:
  Servo_0.attach(4);
  Servo_1.attach(5);
  Servo_2.attach(6);
  Servo_3.attach(8);

}

void loop() {
  // set the position of the servo
  Servo_0.write(90);
  Servo_1.write(90);
  Servo_2.write(90);
  Servo_3.write(170); // closed
}
