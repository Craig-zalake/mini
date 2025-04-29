#define PH_PIN A0  // Analog pin where the pH sensor is connected
#define NUM_SAMPLES 20  // Number of samples for averaging

float calibrationOffset = 0.0 - 0.12; // Adjust this based on calibration with buffer solutions
float voltageToPHConversionFactor = 3.5; // Calibration factor for voltage to pH conversion

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
  Serial.println("pH Sensor Test");
}

void loop() {
  float averageReading = getAverageAnalogReading(PH_PIN); // Get the averaged analog reading
  float voltage = averageReading * (5.0 / 1023.0); // Convert analog reading to voltage (5V reference)
  float pHValue = voltage * voltageToPHConversionFactor + calibrationOffset; // Convert voltage to pH value
  
  // Print the voltage and pH value to the Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(voltage, 3); // Print voltage with 3 decimal places
  Serial.print(" V, ");
  Serial.print("pH Value: ");
  Serial.println(pHValue);

  delay(1000); // Delay for 1 second
}

float getAverageAnalogReading(int pin) {
  long sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += analogRead(pin);  // Read analog value
    delay(20); // Short delay between readings
  }
  return (float)sum / NUM_SAMPLES;
}
