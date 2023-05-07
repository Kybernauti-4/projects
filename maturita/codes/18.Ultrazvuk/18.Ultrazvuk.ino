int trigPin = 2; // nastavuje pin pro ovládání ultrazvukového vysílače
int echoPin = 3; // nastavuje pin pro čtení odraženého signálu od překážky
int duration, distance_cm; // definuje proměnné pro délku trvání signálu a vypočtenou vzdálenost

void setup(){
  Serial.begin(9600); // inicializuje sériovou komunikaci pro výstup naměřené vzdálenosti
  pinMode(echoPin, INPUT); // nastavuje pin pro čtení jako vstupní pin
  pinMode(trigPin, OUTPUT); // nastavuje pin pro ovládání jako výstupní pin
}

void loop(){
  digitalWrite(trigPin, HIGH); // zapíná vysílač ultrazvukového signálu
  delayMicroseconds(10); // čeká 10 mikrosekund
  digitalWrite(trigPin, LOW); // vypíná vysílač ultrazvukového signálu
  duration = pulseIn(echoPin, HIGH); // zjišťuje, jak dlouho trvá signál na echoPin
  distance_cm = (duration / 29.155 ) / 2; // vypočítává vzdálenost v centimetrech
  Serial.println(distance_cm); // vypisuje vzdálenost v centimetrech na sériovou linku
}
