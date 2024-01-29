const int motionSensorPin = 2;
const int indicatorLedPin = 13;
const int activeTimeThreshold = 5000;
void setup()
{
  Serial.begin(9600);
  pinMode(motionSensorPin, INPUT);
  pinMode(indicatorLedPin, OUTPUT);
}
void loop()
{
  // Detect motion
  int isMotionDetected = digitalRead(motionSensorPin);
  // Process the detection
  if (isMotionDetected == HIGH)
  {
    Serial.println("Motion Detected!");
    digitalWrite(indicatorLedPin, HIGH);
    delay(activeTimeThreshold);
  }
  else
  {
    Serial.println("No Motion Detected");
    digitalWrite(indicatorLedPin, LOW);
  }
  delay(500);
}
