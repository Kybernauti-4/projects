const int pin1 = 2;
const int doubleClickDuration = 250; // in milliseconds waits
const int longClickDuration = 500;
const int debounceDelay = 50; // in milliseconds error elimination

int long lastTimeClick = 0;
int lastButtonState = HIGH; // OFF == HIGH (because Arduino has only inbuild pullUP resistor) => to turn it off you need pin the GND pin
int clickCount = 0; // count click interrupts

void setup() {
  Serial.begin(9600); // set baudrate

  pinMode(pin1, INPUT_PULLUP); // pull up => (-) --- button --- (i+) => button with GND and IO pin
  attachInterrupt(digitalPinToInterrupt(pin1), isr, CHANGE); // set interrupt on pin
}

void loop() {
  // nothing to do here
}
// ISR for pin (2)
void isr() {
  int long currentTime = millis();
  int buttonState = digitalRead(pin1); // read pin

  if (buttonState == LOW) {
    lastTimeClick = currentTime; // set last press time
    
  }
  if ((currentTime - lastTimeClick) > debounceDelay) { // the difference must be larger than "bouncing error"
    
    if (buttonState == HIGH){
      handleButtonClick(currentTime - lastTimeClick); // difference between press (lastTimeClick) and release (currentTime)
    }
  }
}

void handleButtonClick(int clickDuration) {
  clickCount++;
  interrupts(); // because it is called from interrupt and it is not possible to interrupt itself (due to enable interrupt it is possible to counting)

  delay(doubleClickDuration); // wait for all double/tripple click

  if (clickCount == 1) {
    if (clickDuration < longClickDuration) {
      Serial.println("Single Click");
      // do something on single click
    } else {
      Serial.println("Long Click");
      // do something on long click
    }
  } else if (clickCount == 2) {
    if (clickDuration < longClickDuration) {
      Serial.println("Double Click");
      // do something on double click
    }
    
  }
  clickCount = 0; // reset click count
}
