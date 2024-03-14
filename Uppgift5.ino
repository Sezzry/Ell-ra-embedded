const int BUTTON_PIN_7 = 2;        
const int BUTTON_PIN_13 = 3;       
const int LED_PIN_9 = 9;           
const int LED_PIN_11 = 11;         
const int POTENTIOMETER_PIN = A0;  
const int PWM_OUTPUT_PIN = 6;      

int buttonState_7 = HIGH;            // Knapp 1: aktuellt tillstånd
int buttonState_13 = HIGH;           // Knapp 2: aktuellt tillstånd
int lastButtonState_7 = HIGH;        // Knapp 1: föregående tillstånd
int lastButtonState_13 = HIGH;       // Knapp 2: föregående tillstånd
unsigned long lastDebounceTime_7 = 0;  // Senaste stabiliseringstidpunkt för knapp 1
unsigned long lastDebounceTime_13 = 0; // Senaste stabiliseringstidpunkt för knapp 2
int debounceDelay = 50;             // Debounce-fördröjningstid för knappar
int ledState_9 = LOW;               // Aktuellt tillstånd för LED 1
int ledState_13 = LOW;              // Aktuellt tillstånd för LED 2
int potValue = 0;                   
bool button1Enabled = true;         // Flagga för om knapp 1 är aktiverad
bool button2Enabled = true;         // Flagga för om knapp 2 är aktiverad
bool potentiometerEnabled = false;  // Flagga för om potentiometern är aktiverad
int currentPower = 0;               // Aktuell effekt för PWM-utspänning

void setup() {
  pinMode(LED_PIN_9, OUTPUT);       
  pinMode(LED_PIN_11, OUTPUT);       
  pinMode(BUTTON_PIN_7, INPUT_PULLUP);  // Knapp 1 inmatning med intern pull-up resistans
  pinMode(BUTTON_PIN_13, INPUT_PULLUP); // Knapp 2 inmatning med intern pull-up resistans
  pinMode(POTENTIOMETER_PIN, INPUT);    
  pinMode(PWM_OUTPUT_PIN, OUTPUT);      

  Serial.begin(9600); 
}

// Huvudloopen
void loop() {
  int reading_7 = digitalRead(BUTTON_PIN_7);   // Läs av knapp 1
  int reading_13 = digitalRead(BUTTON_PIN_13); 

  // Hantera debounce för knapp 1
  if (reading_7 != lastButtonState_7) {
    lastDebounceTime_7 = millis(); // Uppdatera senaste stabiliseringstidpunkt för knapp 1
  }

  if (reading_13 != lastButtonState_13) {
    lastDebounceTime_13 = millis(); 
  }

  // Kontrollera debounce för knapp 1
  if ((millis() - lastDebounceTime_7) > debounceDelay) {
    if (reading_7 != buttonState_7) {
      buttonState_7 = reading_7;

      // Utför åtgärder om knapp 1 trycks ned och är aktiverad
      if (buttonState_7 == LOW && button1Enabled) {
        ledState_9 = !ledState_9;   // Vänd LED 1(Grön) tillstånd
        digitalWrite(LED_PIN_9, ledState_9); // Uppdatera LED 1(Grön) tillstånd
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

  // Uppdatera föregående knapptryckningstillstånd för nästa iteration
  lastButtonState_7 = reading_7;
  lastButtonState_13 = reading_13;

  potValue = analogRead(POTENTIOMETER_PIN);

  // Kontrollera om potentiometern är aktiverad innan användning av värdet
  if (potentiometerEnabled) {
    // Kartlägg potentiometervärdet till PWM-utgångens intervall
    int pwmOutput = map(potValue, 0, 1023, 0, 255);
    analogWrite(PWM_OUTPUT_PIN, pwmOutput); // Uppdatera PWM-utgången

    // Skriv ut potentiometervärdet till den serial monitor
    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);
  }

  delay(200); // Fördröjning på serial monitor, kan ändras efter behov

  // Hantera kommandon från seriell kommunikation om det finns tillgängliga data
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processCommand(command); // Processa mottagna kommandon
  }
}

// Funktion för att processa kommandon från seriell kommunikation
void processCommand(String command) {
  // Hantera kommandon baserat på mottaget meddelande
  if (command.startsWith("enable button 1")) {
    button1Enabled = true; // Aktivera knapp 1
    Serial.println("Button 1 enabled");
  } else if (command.startsWith("disable button 1")) {
    button1Enabled = false; // Inaktivera knapp 1
    Serial.println("Button 1 disabled");
  } else if (command.startsWith("enable button 2")) {
    button2Enabled = true;
    Serial.println("Button 2 enabled");
  } else if (command.startsWith("disable button 2")) {
    button2Enabled = false; 
    Serial.println("Button 2 disabled");
  } else if (command.startsWith("led on 1")) {
    digitalWrite(LED_PIN_9, HIGH); // Tänd LED 1 (Grön)
    Serial.println("LED 1 turned on");
  } else if (command.startsWith("led off 1")) {
    digitalWrite(LED_PIN_9, LOW); // Släck LED 1
    Serial.println("LED 1 turned off");
  } else if (command.startsWith("led on 2")) {
    digitalWrite(LED_PIN_11, HIGH);
    Serial.println("LED 2 turned on");
  } else if (command.startsWith("led off 2")) {
    digitalWrite(LED_PIN_11, LOW); 
    Serial.println("LED 2 turned off");
  } else if (command.startsWith("led power ")) {
    // Hämta målet för effekt från kommandot
    int targetPower = command.substring(10).toInt();

    if (targetPower == -1) {
      // Aktivera potentiometern för styrning av effekt via kommandon led power 
      potentiometerEnabled = true;
      Serial.println("Potentiometer enabled");
    } else {
      // Inaktivera potentiometern och sätt ny effekt
      potentiometerEnabled = false;
      Serial.println("Potentiometer disabled");

      // Säkerställ att måleffekten är inom giltigt intervall (1-10)
      targetPower = constrain(targetPower, 1, 10);

      // Kartlägg måleffekten till PWM-utgångens intervall
      int targetPWM = map(targetPower, 0, 10, 0, 255);

      // Jämnt övergå till ny effekt under en sekund
      unsigned long startTime = millis();
      while (millis() - startTime <= 1000) {
        int i = map(millis() - startTime, 0, 1000, currentPower, targetPWM);
        analogWrite(PWM_OUTPUT_PIN, i); // Uppdatera PWM-utgången
        delay(200); // Fördröjning för jämn övergång, kan justeras för att få en jämnare övergång
      }

      // Uppdatera aktuell effekt och skriv ut till serial monitor
      currentPower = targetPWM;
      Serial.print("LED Power set to ");
      Serial.println(targetPower);
    }
  } else {
    Serial.println("Unknown command"); // Skriver ut okänt kommando om fel kommandon skrivs
  }
}
