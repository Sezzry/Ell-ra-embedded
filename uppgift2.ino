const int potPin = A0; 

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int sensorValue = analogRead(potPin); 
  float voltage = sensorValue * (5.0 / 1023.0); 

  Serial.print("Raw ADC Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(300); 
}
