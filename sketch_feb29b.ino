const int BUTTON_PIN_7 = 2;
const int BUTTON_PIN_13 = 3;
const int LED_PIN_9 = 9;
const int LED_PIN_11 = 11;
const int POTENTIOMETER_PIN = A0;
const int PWM_OUTPUT_PIN = 6;

int ledState_9 = LOW;
int ledState_11 = LOW;
int potValue = 0;
unsigned long lastDebounceTime_7 = 0;
unsigned long lastDebounceTime_13 = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(LED_PIN_9, OUTPUT);
  pinMode(LED_PIN_11, OUTPUT);
  pinMode(BUTTON_PIN_7, INPUT_PULLUP);
  pinMode(BUTTON_PIN_13, INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(PWM_OUTPUT_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_7), buttonInterrupt_7, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_13), buttonInterrupt_13, FALLING);

  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(POTENTIOMETER_PIN);
  int pwmOutput = map(potValue, 0, 1023, 0, 255);
  analogWrite(PWM_OUTPUT_PIN, pwmOutput);

  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  delay(100);
}

void buttonInterrupt_7() {
  if (millis() - lastDebounceTime_7 > debounceDelay) {
    ledState_9 = !ledState_9;
    digitalWrite(LED_PIN_9, ledState_9);
    lastDebounceTime_7 = millis();
  }
}

void buttonInterrupt_13() {
  if (millis() - lastDebounceTime_13 > debounceDelay) {
    ledState_11 = !ledState_11;
    digitalWrite(LED_PIN_11, ledState_11);
    lastDebounceTime_13 = millis();
  }
}
