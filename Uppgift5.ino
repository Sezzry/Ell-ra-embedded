const int BUTTON_PIN_7 = 2;
const int BUTTON_PIN_13 = 3;
const int LED_PIN_9 = 9;
const int LED_PIN_11 = 11;
const int POTENTIOMETER_PIN = A0;
const int PWM_OUTPUT_PIN = 6;

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

bool potentiometerEnabled = false;
int currentPower = 0;

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

  // Check if potentiometer is enabled before using its value
  if (potentiometerEnabled) {
    int pwmOutput = map(potValue, 0, 1023, 0, 255);
    analogWrite(PWM_OUTPUT_PIN, pwmOutput);

    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);
  }

  delay(200);

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processCommand(command);
  }
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
  } else if (command.startsWith("led on 1")) {
    digitalWrite(LED_PIN_9, HIGH);
    Serial.println("LED 1 turned on");
  } else if (command.startsWith("led off 1")) {
    digitalWrite(LED_PIN_9, LOW);
    Serial.println("LED 1 turned off");
  } else if (command.startsWith("led on 2")) {
    digitalWrite(LED_PIN_11, HIGH);
    Serial.println("LED 2 turned on");
  } else if (command.startsWith("led off 2")) {
    digitalWrite(LED_PIN_11, LOW);
    Serial.println("LED 2 turned off");
  } else if (command.startsWith("led power ")) {
    int targetPower = command.substring(10).toInt();

    if (targetPower == -1) {
      // Enable the potentiometer
      potentiometerEnabled = true;
      Serial.println("Potentiometer enabled");
    } else {
      // Disable the potentiometer
      potentiometerEnabled = false;
      Serial.println("Potentiometer disabled");

      // Ensure targetPower is within the valid range (1-10)
      targetPower = constrain(targetPower, 1, 10);

      int targetPWM = map(targetPower, 0, 10, 0, 255);

      // Smoothly change the PWM value
      unsigned long startTime = millis();
      while (millis() - startTime <= 1000) {
        int i = map(millis() - startTime, 0, 1000, currentPower, targetPWM);
        analogWrite(PWM_OUTPUT_PIN, i);
        delay(200);
      }

      currentPower = targetPWM;
      Serial.print("LED Power set to ");
      Serial.println(targetPower);
    }
  } else {
    Serial.println("Unknown command");
  }
}
