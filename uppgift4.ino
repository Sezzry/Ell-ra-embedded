const int buttonPin1 = 13;  // Flytta från pin 3 till 13
const int buttonPin2 = 7;   // Flytta från pin 2 till 7
const int potPin = A0;      
const int ledPinR = 11;     
const int ledPinG = 9;      
const int ledPinB = 3;      

int buttonState1 = 0;       
int buttonState2 = 0;       
int lastButtonState1 = 0;   
int lastButtonState2 = 0;   
int potValue = 0;           

// Variabler debouncing
unsigned long lastDebounceTime1 = 0;  // Senaste stabiliseringstidpunkt för knapp 1
unsigned long lastDebounceTime2 = 0;  // Senaste stabiliseringstidpunkt för knapp 2
unsigned long debounceDelay = 50;     // Debounce-fördröjningstid

void setup() {
  pinMode(buttonPin1, INPUT);  
  pinMode(buttonPin2, INPUT);  
  pinMode(potPin, INPUT);      
  pinMode(ledPinR, OUTPUT);    
  pinMode(ledPinG, OUTPUT);    
  pinMode(ledPinB, OUTPUT);    

  Serial.begin(9600); 
}

void loop() {
  int reading1 = digitalRead(buttonPin1);

  // Om knappens tillstånd har ändrats
  if (reading1 != lastButtonState1) {
    // Uppdatera senaste stabiliseringstidpunkt för knapp 1
    lastDebounceTime1 = millis();
  }

  // Om det har gått tillräckligt med tid sedan senaste stabilisering av knapp 1
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == LOW) {
        digitalWrite(ledPinR, !digitalRead(ledPinR));
      }
    }
  }

  int reading2 = digitalRead(buttonPin2);

  // Om knappens tillstånd har ändrats
  if (reading2 != lastButtonState2) {
    // Uppdatera senaste stabiliseringstidpunkt för knapp 2
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == LOW) {
        digitalWrite(ledPinG, !digitalRead(ledPinG));
      }
    }
  }

  potValue = analogRead(potPin);
  analogWrite(ledPinB, potValue / 4);

  Serial.print("Potentiometer value (LED-B): ");
  Serial.println(potValue);
  
  delay(200);

  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
}
