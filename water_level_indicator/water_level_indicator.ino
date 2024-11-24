// Pin assignments
const int analogInPin = A0; // Sensor analog input
const int greenLED = 2;     // Green LED pin
const int yellowLED = 3;    // Yellow LED pin
const int redLED = 4;       // Red LED pin
const int buzzer = 5;       // Buzzer pin

// Thresholds
const int greenThreshold = 300;  // Green LED threshold
const int yellowThreshold = 500; // Yellow LED threshold
const int redThreshold = 600;    // Red LED & Buzzer threshold

// Averaging setup
const int numReadings = 10;      // Number of readings to average
int readings[numReadings];       // Array to store sensor readings
int readIndex = 0;               // Current index for readings array
int total = 0;                   // Total of readings
int average = 0;                 // Average sensor reading

void setup() {
  // Initialize LED and buzzer pins as output
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Initialize the readings array
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }

  // Start the serial monitor
  Serial.begin(9600);
}

void loop() {
  // Subtract the last reading from the total
  total -= readings[readIndex];

  // Read a new sensor value
  readings[readIndex] = analogRead(analogInPin);

  // Add the new reading to the total
  total += readings[readIndex];

  // Advance to the next index, wrap around if necessary
  readIndex = (readIndex + 1) % numReadings;

  // Calculate the average reading
  average = total / numReadings;

  // Print the average for debugging
  Serial.print("Sensor value (average): ");
  Serial.println(average);

  // LED and buzzer logic
  if (average >= redThreshold) {
    Serial.println("Red condition triggered");
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
  } else if (average >= yellowThreshold) {
    Serial.println("Yellow condition triggered");
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
  } else if (average >= greenThreshold) {
    Serial.println("Green condition triggered");
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
  } else {
    Serial.println("No water detected");
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(100); // Delay to allow sensor values to stabilize
}
