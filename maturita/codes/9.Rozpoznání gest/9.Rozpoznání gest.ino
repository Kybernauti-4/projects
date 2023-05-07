const int pin1 = 2;  // pin tlačítka
const int doubleClickDuration = 400;  // čas čekání na double click (milis)
const int longClickDuration = 300;  // čas od kdy se jedná o long click (milis)
const int debounceDelay = 1;  // čas pro odstranění chyby (milis)

int long lastTimePress = 0;  // čas, kdy bylo naposledy stisknuto
int lastButtonState = HIGH;  // OFF == HIGH (because Arduino has only inbuild pullUP resistor) => to turn it off you need pin the GND pin
int clickCount = 0;  // počítá počet stisknutí během jednoho timeru
int clickDuration = 0;  // jak dlouho trval

int long timerCount = doubleClickDuration+1;  // čas pro timer

bool flag = 0;  // aby se spustil timer pouze jednou (při jedné operaci)

void setup() {
  Serial.begin(9600); // nastaví baudrate (rachlost přenosu a komunikaci)

  pinMode(pin1, INPUT_PULLUP); // pull up => (-) --- button --- (i+) => button with GND and IO pin
  attachInterrupt(digitalPinToInterrupt(pin1), isr, CHANGE);  // rising a falling interrupty moc nefungují
  

  TCCR1A = 0; // Set timer control register A to 0
  TCCR1B = (1 << CS11) | (1 << WGM12); // Set prescaler to 8 and set timer to CTC mode
  OCR1A = 15624; // Set output compare register to 10 milis
  TIMSK1 = (1 << OCIE1A); // Enable timer interrupt
  //perioda = (1 / frekvence časovače) * hodnota předděličky * (hodnota výstupního porovnávacího registru + 1)
}

void loop() {
}
void reset(){
  timerCount = 0;
}

ISR(TIMER1_COMPA_vect) {
  // Timer isr
  timerCount++;  // počítadlo (každý časový úsek)
  if (timerCount == doubleClickDuration/10) {
    clickCount++;  // stisknuto (poprvé)

    // zjisti co bylo zmačknuto:
    if (clickCount == 1) {
      if (clickDuration < longClickDuration) {
        Serial.println("Single Click");
        // single click
      } else {
        Serial.println("Long Click");
        // long click
      }
    } else if (clickCount == 2) {
      if (clickDuration < longClickDuration) {
        Serial.println("Double Click");
        // double click
      }
    }
    clickCount = 0; // vynuluj počet stisknutí
    flag = 0;  // timer už dokončil časový úsek
  }
}

void isr() {
  int long currentTime = millis();  // aktuální čas
  int buttonState = digitalRead(pin1);  // čte hodnotu pinu (tlačítka - negaci)

  if (buttonState == LOW) {  // tlačítko je stisknuto
    lastTimePress = currentTime;  // čas stisknutí
    
  }
  else if ((currentTime - lastTimePress) > debounceDelay && buttonState == HIGH) { // "bouncing error" a tlačítko je puštěno
    clickDuration = currentTime - lastTimePress;  // jak dlouho trvalo stisknutí
    handleButtonClick();
  }
}

void handleButtonClick() {
  if (not flag){
    flag = 1;  // timer běží
    reset();  // spustí timer (vynuluje)
  } else {
    clickCount++;  // další stisknutí
  }
}

/*
//attachInterrupt(digitalPinToInterrupt(pin1), rising, RISING);
//attachInterrupt(digitalPinToInterrupt(pin1), falling, FALLING);

void rising(){  // release - tlačítko puštěno (uvolněno)
  Serial.println("r");
  int long currentTime = millis();  // nastaví aktuální čas
  if ((currentTime - lastTimePress) > debounceDelay) {  // kontroluje "bouncing error"
    clickDuration = currentTime - lastTimePress;  // nastaví čas stisku
    
    if (not flag){
      flag = 1;  //timer běží
      timer();  // zapni x resetuj timer
    
    } else {
      clickCount++;  // pouze přidej jedno stisknutí
    }
  }

}

void falling(){  // press - tlačítko stisknuto
  Serial.println("f");
  int long currentTime = millis();  // nastaví aktuální čas
  lastTimePress = currentTime;  // nastaví začátek stisku
}
*/