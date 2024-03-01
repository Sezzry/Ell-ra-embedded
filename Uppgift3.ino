
const int BUTTON_PIN_7 = 7;  
const int BUTTON_PIN_13 = 13; 
const int LED_PIN_9 = 9;     
const int LED_PIN_11 = 11;    
const int POTENTIOMETER_PIN = A0; 
const int PWM_OUTPUT_PIN = 3;     

int buttonState_7 = 0;       
int buttonState_13 = 0;      
int ledState_9 = LOW;        
int ledState_13 = LOW;       
int potValue = 0;            

void setup() {
  pinMode(LED_PIN_9, OUTPUT);
  pinMode(LED_PIN_11, OUTPUT);
  pinMode(BUTTON_PIN_7, INPUT_PULLUP);
  pinMode(BUTTON_PIN_13, INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(PWM_OUTPUT_PIN, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  buttonState_7 = digitalRead(BUTTON_PIN_7);
  buttonState_13 = digitalRead(BUTTON_PIN_13);

  if (buttonState_7 == LOW) {
    ledState_9 = (ledState_9 == LOW) ? HIGH : LOW;
    digitalWrite(LED_PIN_9, ledState_9);

    while (digitalRead(BUTTON_PIN_7) == LOW) {
      delay(10);
    }
  }

  if (buttonState_13 == LOW) {
    ledState_13 = (ledState_13 == LOW) ? HIGH : LOW;
    digitalWrite(LED_PIN_11, ledState_13);

    while (digitalRead(BUTTON_PIN_13) == LOW) {
      delay(10);
    }
  }

  potValue = analogRead(POTENTIOMETER_PIN);
  int pwmOutput = map(potValue, 0, 1023, 0, 255);

  analogWrite(PWM_OUTPUT_PIN, pwmOutput);

  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
  delay(100); 
}
