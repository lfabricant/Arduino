/* INCLUDE -------- */
#include<Servo.h> 

/* DEFINE -------- */
// Create servo objects
Servo Servo_0;
Servo Servo_1;
Servo Servo_2;
Servo Servo_3;

int SensVal[4] = {0}; // or as an array
 
void setup() {
  // Start the serial
  Serial.begin(9600);

  // Attach the servos on pins to the servo object
  Servo_0.attach(4);
  Servo_1.attach(5);
  Servo_2.attach(6);
  Servo_3.attach(8);

}

void loop() {
  // put your main code here, to run repeatedly:
  ReadPot();

  // Write the potentiometer position to the servo
  Servo_0.write(SensVal[0]);
  Servo_1.write(SensVal[1]);
  Servo_2.write(SensVal[2]);
  Servo_3.write(SensVal[3]);
  
}

void ReadPot(){
  SensVal[0] = analogRead(A0); // read from analog pin 0
  SensVal[1] = analogRead(A1); // read from analog pin 1 
  SensVal[2] = analogRead(A2); // read from analog pin 2 
  SensVal[3] = analogRead(A3); // read from analog pin 3 

  SensVal[0] = map(SensVal[0],0,1024,0,170);
  SensVal[1] = map(SensVal[1],0,1024,0,170);
  SensVal[2] = map(SensVal[2],0,1024,0,170);
  SensVal[3] = map(SensVal[3],0,1024,0,175); 

  Serial.print("SensVal[0]: ");
  Serial.print(SensVal[0]);
  Serial.print(" | ");
  Serial.print("SensVal[1]: ");
  Serial.print(SensVal[1]);
  Serial.print(" | ");
  Serial.print("SensVal[2]: ");
  Serial.print(SensVal[2]);
  Serial.print(" | ");
  Serial.print("SensVal[3]: ");
  Serial.print(SensVal[3]);
  Serial.println(" | ");
  
}
