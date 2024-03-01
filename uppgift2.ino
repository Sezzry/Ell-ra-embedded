const int potPin = A0; // Connect the potentiometer to analog pin A0

void setup() {
  Serial.begin(9600); // Start serial communication with a baud rate of 9600
}

void loop() {
  int sensorValue = analogRead(potPin); // Read the value from the potentiometer
  float voltage = sensorValue * (5.0 / 1023.0); // Convert ADC value to voltage (assuming 5V reference)

  Serial.print("Raw ADC Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(300); // Wait for 300 milliseconds before the next reading
}
