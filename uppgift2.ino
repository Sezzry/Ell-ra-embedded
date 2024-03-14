const int potPin = A0; 

void setup() {
  Serial.begin(9600); 
}

void loop() {
  // Läser av värdet från potentiometer 
  int sensorValue = analogRead(potPin); 

  // Spänningen är 5v
  // Formeln multiplicerar det analoga värdet med förhållandet mellan 5V och 1023
  float voltage = sensorValue * (5.0 / 1023.0); 

  // Skriver ut det råa ADC värdet och spänningen till serieporten
  Serial.print("Raw ADC Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(300); 
}
