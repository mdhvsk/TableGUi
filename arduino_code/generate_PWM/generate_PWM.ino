// Pin number for PWM output
const int pwmPin = 2;

// Variables for timing
unsigned long previousMillis = 0; // Stores the previous time
unsigned long intervalOn = 2000; // Default interval for ON time in milliseconds (5 seconds)
unsigned long intervalOff = 5000; // Default interval for OFF time in milliseconds (7 seconds)
int dutyCycle = 50; // Default duty cycle in percentage (50%)

// Function to generate PWM signal
void generatePWM(unsigned long onTime, unsigned long offTime, int duty) {
  unsigned long currentMillis = millis(); // Get the current time
  unsigned long elapsedMillis = currentMillis - previousMillis; // Calculate elapsed time since last update

  // Check if it's time to turn ON the PWM signal
  if (elapsedMillis <= onTime && !digitalRead(pwmPin)) {
    // Set PWM signal ON with specified duty cycle
    analogWrite(pwmPin, duty * 255 / 100); // Convert duty cycle percentage to PWM value
  }

  // Check if it's time to turn OFF the PWM signal
  if (elapsedMillis > onTime && digitalRead(pwmPin)) {
    // Set PWM signal OFF
    analogWrite(pwmPin, 0); // 0% duty cycle (fully OFF)
  }

  // Check if it's time to update the PWM timing
  if (elapsedMillis >= onTime + offTime) {
    // Update the previousMillis and intervalOff
    previousMillis = currentMillis;
    intervalOff = offTime;
  }
}

void setup() {
  // Set the PWM pin as an OUTPUT
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Call the generatePWM function with specified parameters
  generatePWM(intervalOn, intervalOff, dutyCycle);
  Serial.println(analogRead(A0));
}