#include <IRremote.h> // include IRremote library

// variables
#define PIN_SERVO  2    //define servo pin
#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT 4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT 6
#define PIN_IRREMOTE_RECV 9 // infrared receiving pin

// define the IR key
#define IR_REMOTE_KEYCODE_UP 0xFF02FD
#define IR_REMOTE_KEYCODE_DOWN 0xFF9867
#define IR_REMOTE_KEYCODE_LEFT 0xFFE01F 
#define IR_REMOTE_KEYCODE_RIGHT 0xFF906F 

#define IR_REMOTE_KEYCODE_PLAY 0xFFA857

#define IR_REMOTE_KEYCODE_ZERO 0xFF6897
#define IR_REMOTE_KEYCODE_ONE 0xFF30CF
#define IR_REMOTE_KEYCODE_TWO 0xFF18E7

#define IR_UPDATE_TIMEOUT 120 // time without a signal to say stop
#define IR_CAR_SPEED 180 // pwm command to send to the car

IRrecv irrecv(PIN_IRREMOTE_RECV); // create a class object to receive data
decode_results results; // create a decoding results class object

u32 currentKeyCode, lastKeyCode; // 32 bits to store large numbers (int is too small)
bool isStopFromIR = false;
u32 lastIRUpdateTime = 0; // check if irtimeout > difference

// SET UP BUZZER
#define PIN_BATTERY     A0
#define PIN_BUZZER      A0

// SET UP LED
#include "Freenove_WS2812B_RGBLED_Controller.h"
#define I2C_ADDRESS  0x20
#define LEDS_COUNT   10  //it defines number of lEDs. 
Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB); //initialization

// SET UP ULTRASONIC RANGING
#include "Servo.h"
#define PIN_SONIC_TRIG    7    //define Trig pin
#define PIN_SONIC_ECHO    8    //define Echo pin
#define MAX_DISTANCE    300   //cm
#define SONIC_TIMEOUT   (MAX_DISTANCE*60) // calculate timeout 
#define SOUND_VELOCITY  340  //soundVelocity: 340m/s
Servo servo;             //create servo object
byte servoOffset = 0;    //change the value to Calibrate servo
u8 distance[4];          //define an arry with type u8(same to unsigned char)

void setup() {
  irrecv.enableIRIn(); // start the receiver
  
  pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
  pinMode(PIN_DIRECTION_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
  
  Serial.begin(9600); // initialize the serial port - rate of communication arduino 

  // BUZZER
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, HIGH);
  delay(100);
  digitalWrite(PIN_BUZZER, LOW);

  // ULTRASONIC RANGING
  pinMode(PIN_SONIC_TRIG, OUTPUT);// set trigPin to output mode
  pinMode(PIN_SONIC_ECHO, INPUT); // set echoPin to input mode
  servo.attach(PIN_SERVO);        //initialize servo 
  servo.write(90 + servoOffset);  // change servoOffset to Calibrate servo
}

void loop() {
  
  if (irrecv.decode(&results)){ // if there is something to decode (if you get a signal - will pause IR receiver)
    isStopFromIR = false;
    currentKeyCode = results.value;
    Serial.println(currentKeyCode); // print out decoded results in hex because of size
    if(currentKeyCode != 0xFFFFFFFF) {
      lastKeyCode = currentKeyCode;         
    }
    switch(lastKeyCode){
      case IR_REMOTE_KEYCODE_UP:
        motorRun(IR_CAR_SPEED, IR_CAR_SPEED); // move forward if UP
        delay(100);
        motorRun(0,0);
        break;
      
      case IR_REMOTE_KEYCODE_DOWN:
        motorRun(-IR_CAR_SPEED, -IR_CAR_SPEED); // move backward if DOWN
        delay(100);
        motorRun(0,0);
        break;

      case IR_REMOTE_KEYCODE_LEFT:
        motorRun(-IR_CAR_SPEED, IR_CAR_SPEED); // turn left if LEFT
        delay(100);
        motorRun(0,0);
        break;
      
      case IR_REMOTE_KEYCODE_RIGHT:
        motorRun(IR_CAR_SPEED, -IR_CAR_SPEED); // turn right if RIGHT
        delay(100);
        motorRun(0,0);
        break;

      case IR_REMOTE_KEYCODE_PLAY:
         for (int i = 0; i < 4; i++) {
            digitalWrite(PIN_BUZZER, HIGH); //turn on buzzer
            delay(100);
            digitalWrite(PIN_BUZZER, LOW);  //turn off buzzer
            delay(100);
          }
           delay(500);
         break;

      case IR_REMOTE_KEYCODE_ZERO:
        while (!strip.begin());
        strip.setAllLedsColor(0xFF0000); //Set all LED color to red
        break;

      case IR_REMOTE_KEYCODE_ONE:
        while (!strip.begin());
        strip.setAllLedsColor(255,255,0); //Set all LED color to yellow
        break;

      case IR_REMOTE_KEYCODE_TWO:
        while (!strip.begin());
        strip.setAllLedsColor(0x0000FF); //Set all LED color to red
        break;

      default:
        while (!strip.begin());
        strip.setAllLedsColor(0,0,0);
        break;
    }

    irrecv.resume(); // receive the next value
    lastIRUpdateTime = millis(); // write down current time
    //ultrasonic_loop();
    
  } 
  
}

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
}

void ultrasonic_loop() {
  servo.write(45); // IR timeout without a delay
  delay(1000);
  distance[0] = getSonar();   //get ultrsonice value and save it into distance[0]

  servo.write(90);
  delay(1000);
  distance[1] = getSonar();

  servo.write(135);
  delay(1000);
  distance[2] = getSonar();

  servo.write(90);
  delay(1000);
  distance[3] = getSonar();
  
  Serial.print("Distance L / M / R / M2:   ");  //Left/Middle/Right/Middle2
  for (int i = 0; i < 4; i++) {
    Serial.print(distance[i]);     //print ultrasonic in 45°, 90°, 135°, 90°
    Serial.print("/");
  }
  Serial.print('\n');  //next content will be printed in new line
  return;
}

float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(PIN_SONIC_TRIG, HIGH); // make trigPin output high level lasting for 10μs to triger HC_SR04,
  delayMicroseconds(10);
  digitalWrite(PIN_SONIC_TRIG, LOW);
  pingTime = pulseIn(PIN_SONIC_ECHO, HIGH, SONIC_TIMEOUT); // Wait HC-SR04 returning to the high level and measure out this waitting time
  if (pingTime != 0)
    distance = (float)pingTime * SOUND_VELOCITY / 2 / 10000; // calculate the distance according to the time
  else
    distance = MAX_DISTANCE;
  return distance; // return the distance value
}

// + = FF02FD
// - = FF9867
// < = FFE01F
// > = FF906F
// play = FFA857
// 0 = FF6897
// 1 = FF30CF
// 2 = FF18E7
// 3 = FF7A85
// 4 = FF10EF
// 5 = FF38C7
// 6 = FF5AA5
// 7 = FF42BD
// 8 = FF4AB5
// 9 = FF52AD
// C = FFB04F
// test = FF22DD
// back = FFC23D
// power = FFA25D
// menu = FFE21D
