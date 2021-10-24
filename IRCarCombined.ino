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

#define IR_UPDATE_TIMEOUT 120 // time without a signal to say stop
#define IR_CAR_SPEED 180 // pwm command to send to the car

IRrecv irrecv(PIN_IRREMOTE_RECV); // create a class object to receive data
decode_results results; // create a decoding results class object

u32 currentKeyCode, lastKeyCode; // 32 bits to store large numbers (int is too small)
bool isStopFromIR = false;
u32 lastIRUpdateTime = 0; // check if irtimeout > difference

void setup() {
  irrecv.enableIRIn(); // start the receiver
  
  pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
  pinMode(PIN_DIRECTION_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);

  Serial.begin(9600); // initialize the serial port - rate of communication arduino 
}

void loop() {
  if (irrecv.decode(&results)){ // if there is something to decode (if you get a signal - will pause IR receiver)
    isStopFromIR = false;
    currentKeyCode = results.value;
    Serial.println(currentKeyCode); // print out decoded results in hex because of size
    if(currentKeyCode != 0xFFFFFFFF) {
      lastKeyCode = currentKeyCode;         // *****error msg?*****
    }
    switch(lastKeyCode){
      case IR_REMOTE_KEYCODE_UP:
        motorRun(IR_CAR_SPEED, IR_CAR_SPEED); // move forward if UP
        break;
      
      case IR_REMOTE_KEYCODE_DOWN:
        motorRun(-IR_CAR_SPEED, -IR_CAR_SPEED); // move backward if DOWN
        break;
      
      case IR_REMOTE_KEYCODE_LEFT:
        motorRun(-IR_CAR_SPEED, IR_CAR_SPEED); // turn left if LEFT
        break;
      
      case IR_REMOTE_KEYCODE_RIGHT:
        motorRun(IR_CAR_SPEED, -IR_CAR_SPEED); // turn right if RIGHT
        break;

      default:
        break;
    }

    irrecv.resume(); // receive the next value
    lastIRUpdateTime = millis(); // write down current time
  } 
  else {
    if(millis()-lastIRUpdateTime > IR_UPDATE_TIMEOUT) {
      if(!isStopFromIR){
        isStopFromIR = true;
        motorRun(0,0);
      }
      lastIRUpdateTime = millis();
    }
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
