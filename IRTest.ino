#include <IRremote.h> // include IRremote library
#define PIN_IRREMOTE_RECV 9 // infrared receiving pin

IRrecv irrecv(PIN_IRREMOTE_RECV); // create a class object to receive data

decode_results results; // create a decoding results class object

void setup() {
  Serial.begin(9600); // initialize the serial port - rate of communication arduino 
  irrecv.enableIRIn(); // start the receiver
}

void loop() {
  if (irrecv.decode(&results)){ // if there is something to decode (if you get a signal - will pause IR receiver)
    Serial.println(results.value,HEX); // print out decoded results in hex because of size
    irrecv.resume();
  }
  delay(100);
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
