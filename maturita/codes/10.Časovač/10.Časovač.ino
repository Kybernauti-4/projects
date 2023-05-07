int ledPin = 3; // LED pin
volatile unsigned long timerCount = 0; // Timer count

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  TCCR1A = 0; // Set timer control register A to 0
  TCCR1B = (1 << CS11) | (1 << WGM12); // Set prescaler to 8 and set timer to CTC mode
  OCR1A = 15624; // Set output compare register to 10 milis
  TIMSK1 = (1 << OCIE1A); // Enable timer interrupt

  //perioda = (1 / frekvence časovače) * hodnota předděličky * (hodnota výstupního porovnávacího registru + 1)
}

void loop() {
  // Do something in the loop if needed
}

ISR(TIMER1_COMPA_vect) {
  // Timer interrupt routine
  timerCount++;
  if (timerCount == 100) { // 1 second interval
    analogWrite(ledPin, 127); // Set PWM to 50%
    // do something
  }
  else if (timerCount == 200) { // 2 second interval
    analogWrite(ledPin, 255); // Set PWM to 100%
    // do something
    timerCount = 0; // Reset timer count
  }
}
