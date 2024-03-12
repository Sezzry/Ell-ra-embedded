const int BUTTON_PIN_7 = 7;  
const int BUTTON_PIN_13 = 13; 
const int LED_PIN_9 = 9;     
const int LED_PIN_11 = 11;    
const int POTENTIOMETER_PIN = A0; 
const int PWM_OUTPUT_PIN = 3;     

int buttonState_7 = HIGH;   
int buttonState_13 = HIGH;  
int lastButtonState_7 = HIGH;
int lastButtonState_13 = HIGH;
unsigned long lastDebounceTime_7 = 0;
unsigned long lastDebounceTime_13 = 0;
int debounceDelay = 50;     
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
  int reading_7 = digitalRead(BUTTON_PIN_7);
  int reading_13 = digitalRead(BUTTON_PIN_13);

  if (reading_7 != lastButtonState_7) {
    lastDebounceTime_7 = millis();
  }

  if (reading_13 != lastButtonState_13) {
    lastDebounceTime_13 = millis();
  }

  if ((millis() - lastDebounceTime_7) > debounceDelay) {
    if (reading_7 != buttonState_7) {
      buttonState_7 = reading_7;

      if (buttonState_7 == LOW) {
        ledState_9 = !ledState_9;
        digitalWrite(LED_PIN_9, ledState_9);
      }
    }
  }

  if ((millis() - lastDebounceTime_13) > debounceDelay) {
    if (reading_13 != buttonState_13) {
      buttonState_13 = reading_13;

      if (buttonState_13 == LOW) {
        ledState_13 = !ledState_13;
        digitalWrite(LED_PIN_11, ledState_13);
      }
    }
  }

  lastButtonState_7 = reading_7;
  lastButtonState_13 = reading_13;

  potValue = analogRead(POTENTIOMETER_PIN);
  int pwmOutput = map(potValue, 0, 1023, 0, 255);
  analogWrite(PWM_OUTPUT_PIN, pwmOutput);

  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  delay(100);
}
