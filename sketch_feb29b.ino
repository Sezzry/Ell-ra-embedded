const int BUTTON_PIN_7 = 7;
const int BUTTON_PIN_13 = 13;
const int LED_PIN_9 = 9;
const int LED_PIN_11 = 11;
const int POTENTIOMETER_PIN = A0;
const int PWM_OUTPUT_PIN = 5;

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
bool button1Enabled = true;
bool button2Enabled = true;

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

      if (buttonState_7 == LOW && button1Enabled) {
        ledState_9 = !ledState_9;
        digitalWrite(LED_PIN_9, ledState_9);
      }
    }
  }

  if ((millis() - lastDebounceTime_13) > debounceDelay) {
    if (reading_13 != buttonState_13) {
      buttonState_13 = reading_13;

      if (buttonState_13 == LOW && button2Enabled) {
        ledState_13 = !ledState_13;
        digitalWrite(LED_PIN_11, ledState_13);
      }
    }
  }

  lastButtonState_7 = reading_7;
  lastButtonState_13 = reading_13;

  potValue = analogRead(POTENTIOMETER_PIN);
  int pwmOutput = map(potValue, 0, 255, 0, 10); 
  analogWrite(PWM_OUTPUT_PIN, pwmOutput);

  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processCommand(command);
  }

  delay(1000);
}

void processCommand(String command) {
  if (command.startsWith("enable button 1")) {
    button1Enabled = true;
    Serial.println("Button 1 enabled");
  } else if (command.startsWith("disable button 1")) {
    button1Enabled = false;
    Serial.println("Button 1 disabled");
  } else if (command.startsWith("enable button 2")) {
    button2Enabled = true;
    Serial.println("Button 2 enabled");
  } else if (command.startsWith("disable button 2")) {
    button2Enabled = false;
    Serial.println("Button 2 disabled");
  } else if (command.startsWith("Ledon 1")) {
    digitalWrite(LED_PIN_9, HIGH);
    Serial.println("LED 1 turned on");
  } else if (command.startsWith("Ledoff 1")) {
    digitalWrite(LED_PIN_9, LOW);
    Serial.println("LED 1 turned off");
  } else if (command.startsWith("Ledon 2")) {
    digitalWrite(LED_PIN_11, HIGH);
    Serial.println("LED 2 turned on");
  } else if (command.startsWith("ledpower ")) {
    int targetPower = command.substring(10).toInt();
    int currentPower = analogRead(PWM_OUTPUT_PIN);
  
    for (int i = 0; i <= 100; ++i) {
        int intermediatePower = map(i, 0, 100, currentPower, targetPower);
        analogWrite(PWM_OUTPUT_PIN, intermediatePower);
        delay(200); 
    }
    
    Serial.print("LED Power set to ");
    Serial.println(targetPower);
}

    Serial.println("Unknown command");
  }
