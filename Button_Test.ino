int ButtonPin = 3;
int ButtonVal = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ButtonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ButtonVal = digitalRead(ButtonPin);

  // The button is 5V by default, so we have to look at opposite of value

  if (!ButtonVal == HIGH) // if the button value is low (button is high by default)
  {
      Serial.println("The button is pressed.");
      for(int i = 1; i <= 10; i++){
        Serial.println(i);
        delay(100); // corresponds to ms
      }
  }
