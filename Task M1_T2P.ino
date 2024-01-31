const int sensorPin = 4;
const int ledPin = 8;
const int buttonPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), sensorInterruptHandler, CHANGE);
}

void loop() {
  // Check for motion
  int motionState = digitalRead(sensorPin);

  // Process motion detection
  if (motionState == HIGH) {
    Serial.println("Interrupt Detected!");
    digitalWrite(ledPin, HIGH);
    delay(2000);
  } else {
    Serial.println("No Interrupt Detected");
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}

void sensorInterruptHandler() {
  // Toggle the LED state when button state changes
  digitalWrite(ledPin, HIGH);
}
