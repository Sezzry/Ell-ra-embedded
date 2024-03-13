const int buttonPin1 = 13; 
const int buttonPin2 = 7;  
const int potPin = A0;    
const int ledPinR = 11;    
const int ledPinG = 9;     
const int ledPinB = 3;     

int buttonState1 = 0;      
int buttonState2 = 0;      
int lastButtonState1 = 0;  
int lastButtonState2 = 0;  
int potValue = 0;          

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
  buttonState1 = digitalRead(buttonPin1);

  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == LOW) {
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
  analogWrite(ledPinB, potValue / 4); 

  Serial.print("Potentiometer value (LED-B): ");
  Serial.println(potValue);
  delay(200);

  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
}
