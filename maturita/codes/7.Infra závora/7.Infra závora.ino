const int infra_zavora = 2; // přiřazení čísla pinu 2 k proměnné infra_zavora

void setup() {
  pinMode(infra_zavora, INPUT); // nastavení pinu 2 jako vstupu
  Serial.begin(9600); // zapnutí sériové komunikace s rychlostí 9600 baudů
}

void loop() {
  int stav_zavora = digitalRead(infra_zavora); // čtení stavu závory na pinu 2
  Serial.print("Stav zavor: "); // výpis na sériovou linku
  Serial.println(stav_zavora);
  delay(100); // krátké zpoždění pro stabilitu čtení
}
