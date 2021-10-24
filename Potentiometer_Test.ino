/* int PotVal0 = 0; // we could define each potentiometer 
   int PotVal1 = 0; // holder individually
   int PotVal2 = 0;
   int PotVal3 = 0; 
 */ 

int SensVal[4] = {0}; // or as an array
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadPot();
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
