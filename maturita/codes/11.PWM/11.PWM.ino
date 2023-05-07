//Pin 3 (digital pwm pin) + LED - GND

int ledPin = 3; // definujeme pin pro LED
int brightness = 0; // nastavujeme jas LED

void setup() {
pinMode(ledPin, OUTPUT); // nastavíme pin pro LED jako výstup
}

void loop() {
for (brightness = 0; brightness <= 255; brightness += 5) { // postupně zvyšujeme jas v krocích
analogWrite(ledPin, brightness); // nastavíme jas LED pomocí PWM
delay(50); // počkáme krátkou dobu před změnou jasu
}

for (brightness = 255; brightness >= 0; brightness -= 5) { // postupně snižujeme jas v krocích
analogWrite(ledPin, brightness); // nastavíme jas LED pomocí PWM
delay(50); // počkáme krátkou dobu před změnou jasu
}
}