// Define the pin numbers for LED and potentiometer
const byte LED_PIN = 13;
const byte METER_PIN = A4;

void setup()
{
  // Set LED pin as output and potentiometer pin as input
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Serial communication initialized.");
  
  // Read initial timer frequency from the potentiometer
  double initialFrequency = readPotentiometer();
  Serial.print("Initial frequency: ");
  Serial.print(initialFrequency);
  Serial.println(" Hz");
  
  // Start timer with initial frequency
  startTimer(initialFrequency);
  Serial.println("Timer started.");
}

void loop()
{ 
  // Continuously read the potentiometer value and update timer frequency
  double frequency = readPotentiometer();
  Serial.print("Current frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");
  
  startTimer(frequency);
  
  // Delay for 2 seconds (2000 milliseconds)
  delay(2000);
}

// Function to configure and start the timer with a specified frequency
void startTimer(double timerFrequency){
  // Disable interrupts while configuring timer registers
  noInterrupts();
  
  // Calculate the value for OCR1A (Output Compare Register A)
  unsigned long ocrValue = F_CPU / (2 * 1024 * timerFrequency) - 1; // Assuming prescaler is set to 1024
  
  // Set the value for OCR1A
  OCR1A = ocrValue;
  
  // Configure Timer1 for CTC (Clear Timer on Compare Match) mode
  TCCR1A = 0; // Clear Timer1 control register A
  TCCR1B = (1 << WGM12); // Set WGM12 bit for CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
  
  // Enable Timer1 compare match A interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // Re-enable interrupts
  interrupts();
}

// Interrupt service routine for handling timer compare match event
ISR(TIMER1_COMPA_vect){
   // Toggle the state of the LED pin
   digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
   Serial.println("LED toggled.");
}

// Function to read the potentiometer value and map it to a frequency range
double readPotentiometer() {
  // Read analog value from the potentiometer
  int potValue = analogRead(METER_PIN);
  
  // Map the potentiometer value to a timer frequency range (adjust as needed)
  double frequency = map(potValue, 0, 1023, 0.1, 10.0); // Example range: 0.1 Hz to 10 Hz
  
  // Print the mapped frequency for debugging purposes
  return frequency;
}
