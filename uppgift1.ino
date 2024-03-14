const int redLedPin = 11;  
const int greenLedPin = 9; 
const int blueLedPin = 3; //flytta till led pin 3 till 6 

// definierar led pinsen som output.
void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop() {
  digitalWrite(redLedPin, HIGH); // tänder röda lampan
  delay(1000); // vänta 1 sekund
  digitalWrite(redLedPin, LOW); // släcker röda

  digitalWrite(greenLedPin, HIGH);
  delay(1000);
  digitalWrite(greenLedPin, LOW);

  digitalWrite(blueLedPin, HIGH);
  delay(1000); 
  digitalWrite(blueLedPin, LOW);

  delay(1000);
}

// I = V/R = 5V/220 ohm
// I = 5/220 = 0.0227 A ungefär för varje diod
// Strömmen är ca 22.7 mA milliampeere per diod
