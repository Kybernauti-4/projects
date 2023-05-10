const int pin1 = 2;  // pin tlačítka
const int doubleClickDuration = 600;  // čas čekání na double click (milis)
const int longClickDuration = 500;  // čas od kdy se jedná o long click (milis)
const int debounceDelay = 5;  // čas pro odstranění chyby (milis)

int long lastTimePress = 0;  // čas, kdy bylo naposledy stisknuto
int lastButtonState = HIGH;  // OFF == HIGH (because Arduino has only inbuild pullUP resistor) => to turn it off you need pin the GND pin
int clickCount = 0;  // počítá počet stisknutí během jednoho timeru
int clickDuration = 0;  // jak dlouho trval

int long flag = 0; // čas posledního puštění "timeru"

void setup() {
  Serial.begin(9600); // nastaví baudrate (rachlost přenosu a komunikaci)

  pinMode(pin1, INPUT_PULLUP); // pull up => (io+) --- button --- (GND) => button with GND and IO pin
  attachInterrupt(digitalPinToInterrupt(pin1), isr, CHANGE);  // rising a falling interrupty moc nefungují
}

void loop() {
  noInterrupts();
  if ((clickCount >= 1) && millis()-flag>doubleClickDuration) {    
    eventHandler();
    clickCount = 0; // vynuluj počet stisknutí
    lastButtonState = HIGH; // opraví případné chyby
    

  }
  interrupts();
  delay(1);
}

void eventHandler(){
  // zjisti co bylo zmačknuto:
    if (clickCount == 1) {

      if (clickDuration < longClickDuration) {
        Serial.print("Single Click ");
        // single click
      } else {
        Serial.print("Long Click ");
        // long click
      }
    } else if (clickCount == 2) {
      if (clickDuration < longClickDuration) {
        Serial.print("Double Click ");
        // double click
      }
    }
    Serial.println(clickCount);
    
}

void isr() {
  int long currentTime = millis();  // aktuální čas
  int buttonState = digitalRead(pin1);  // čte hodnotu pinu (tlačítka - negaci)
  flag = millis();
  

  if (buttonState == LOW && !(lastButtonState == buttonState)) {  // tlačítko je stisknuto
    lastTimePress = currentTime;  // čas stisknutí
    lastButtonState = buttonState;
    
    
  }
  else if (buttonState == HIGH && !(lastButtonState == buttonState)) { // "bouncing error" a tlačítko je puštěno
    clickDuration = currentTime - lastTimePress;  // jak dlouho trvalo stisknutí
    if (clickDuration>debounceDelay){
      lastButtonState = buttonState;
      //Serial.println("Release");
      handleButtonClick();
    }
    
  }
}

void handleButtonClick() {
  if (clickCount == 0){
    clickCount++;  // stisknuto (poprvé)
    
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