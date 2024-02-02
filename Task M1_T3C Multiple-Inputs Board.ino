const int pirPin1 = 4;   // First PIR sensor
const int pirPin2 = 5;   // Second PIR sensor
const int ledPin1 = 2;   // First LED
const int ledPin2 = 7;   // Second LED

bool isPir1Active = true;
bool isPir2Active = true;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(pirPin1), togglePir1, FALLING);
  attachInterrupt(digitalPinToInterrupt(pirPin2), togglePir2, FALLING);
}

void loop() {
  checkPirSensors();
}

void checkPirSensors() {
  int pirValue1 = digitalRead(pirPin1);
  int pirValue2 = digitalRead(pirPin2);

  Serial.print("PIR Sensor 1: ");
  Serial.println(pirValue1);
  Serial.print("PIR Sensor 2: ");
  Serial.println(pirValue2);

  // Update LEDs based on PIR sensor readings
  digitalWrite(ledPin1, pirValue1);  // LED 1 on if motion detected by sensor 1
  digitalWrite(ledPin2, pirValue2);  // LED 2 on if motion detected by sensor 2

  // Print messages when motion is detected
  if (pirValue1 == HIGH && isPir1Active) {
    Serial.println("Motion detected by Sensor 1! LED 1 Glowing!");
  }

  if (pirValue2 == HIGH && isPir2Active) {
    Serial.println("Motion detected by Sensor 2! LED 2 Glowing!");
  }

  delay(500);  // Adjust delay as needed
}

void togglePir1() {
  isPir1Active = !isPir1Active;
  Serial.print("PIR Sensor 1 toggled. Active sensor: ");
  Serial.println(isPir1Active ? "Active" : "Inactive");
  delay(500);  // Debounce the button
}

void togglePir2() {
  isPir2Active = !isPir2Active;
  Serial.print("PIR Sensor 2 toggled. Active sensor: ");
  Serial.println(isPir2Active ? "Active" : "Inactive");
  delay(500);  // Debounce the button
}
