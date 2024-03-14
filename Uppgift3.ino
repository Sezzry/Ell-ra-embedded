const int buttonPin1 = 3;  // Knapp 1, flytta pin till 13 eller använd pin 3
const int buttonPin2 = 2;   // Knapp 2, flytta pin till 7 eller använd pin 2
const int potPin = A0;      // Potentiometer
const int ledPinR = 11;     // Röd LED
const int ledPinG = 9;      // Grön LED
const int ledPinB = 3;      // Blå LED

int buttonState1 = 0;       // Knapp 1 aktuellt tillstånd
int buttonState2 = 0;       // Knapp 2 aktuellt tillstånd
int lastButtonState1 = 0;   // Knapp  föregående tillstånd
int lastButtonState2 = 0;   // Knapp 2 föregående tillstånd
int potValue = 0;           // Potentiometervärde

void setup() {
  pinMode(buttonPin1, INPUT);  // Inmatning knapp 1
  pinMode(buttonPin2, INPUT);  // Inmatning knapp 2
  pinMode(potPin, INPUT);      // Inmatning potentiometer
  pinMode(ledPinR, OUTPUT);    // Utgång Röd LED
  pinMode(ledPinG, OUTPUT);    // Utgång Grön LED
  pinMode(ledPinB, OUTPUT);    // Utgång Blå LED

  Serial.begin(9600); 
}

void loop() {
  // Läs knapp 1
  buttonState1 = digitalRead(buttonPin1);

  // Kollar om knappens tillstånd har ändrats
  if (buttonState1 != lastButtonState1) {
    // Kollar om knappen trycks ned
    if (buttonState1 == LOW) {
      // Vänd på den röda LED ljuset (tänd om släckt, släck om tänd)
      digitalWrite(ledPinR, !digitalRead(ledPinR));
    }
  }

  buttonState2 = digitalRead(buttonPin2);

  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == LOW) {
      digitalWrite(ledPinG, !digitalRead(ledPinG));
    }
  }

  potValue = analogRead(potPin);
  // Skicka ut potentiometervärde som PWM-signal till den blå ljuset
  analogWrite(ledPinB, potValue / 4); // Dela värdet för att anpassa till 0-255

  // Skriv ut potentiometervärdet till serial monitor
  Serial.print("Potentiometer value (LED-B): ");
  Serial.println(potValue);
  
  // Fördröjning för att undvika att överbelasta seriell kommunikation, fördröjning kan justeras efter behov
  delay(200);

  // Uppdatera föregående knapptryckningstillstånd
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
}
