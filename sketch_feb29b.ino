const int redLedPin = 9;  
const int greenLedPin = 10; 
const int blueLedPin = 11;  

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop() {
  digitalWrite(redLedPin, HIGH);
  delay(1000);
  digitalWrite(redLedPin, LOW);

  digitalWrite(greenLedPin, HIGH);
  delay(1000);
  digitalWrite(greenLedPin, LOW);

  digitalWrite(blueLedPin, HIGH);
  delay(1000); 
  digitalWrite(blueLedPin, LOW);

  delay(1000);
}
