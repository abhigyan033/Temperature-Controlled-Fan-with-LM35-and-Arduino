// Define pin connections
const int sensorPin = A0;   // LM35 output connected to A0
const int fanPin = 9;       // Fan control connected to digital pin 9 (PWM)

// Define temperature thresholds (in Celsius)
const int minTemp = 25;     // Fan starts spinning at this temp
const int maxTemp = 50;     // Fan runs at full speed at this temp

void setup() {
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600); // Start serial communication for debugging
}

void loop() {
  // Read the analog value from the LM35 (0-1023)
  int sensorValue = analogRead(sensorPin);

  // Convert the analog reading to voltage (0-5V)
  float voltage = sensorValue * (5.0 / 1023.0);

  // Convert voltage to temperature in Celsius (10mV per degree)
  float temperature = voltage * 100;

  // Print the temperature to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Map the temperature to a PWM value (0-255)
  // If temp is below minTemp, fan is off (PWM = 0).
  // If temp is between minTemp and maxTemp, fan speed scales.
  // If temp is above maxTemp, fan is at max (PWM = 255).
  int pwmValue = 0;
  if (temperature > minTemp) {
    pwmValue = map(temperature, minTemp, maxTemp, 50, 255); // Minimum PWM of 50 to start the fan
    pwmValue = constrain(pwmValue, 50, 255); // Ensure PWM stays within 50-255 range
  } else {
    pwmValue = 0; // Turn fan off if below minimum temperature
  }

  // Write the PWM value to the fan pin
  analogWrite(fanPin, pwmValue);

  // Print the PWM value for debugging
  Serial.print("PWM Value: ");
  Serial.println(pwmValue);
  Serial.println("-----");

  delay(2000); // Wait for 2 seconds 
}
