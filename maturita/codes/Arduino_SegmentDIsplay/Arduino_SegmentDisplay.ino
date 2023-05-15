#include <Arduino.h>

const int arr_position[] = {2, 3, 4, 5}; // Definování pinů pro pozici (1, 2, 3, 4) - rezistory
const int arr_segment[] = {6, 7, 8, 9, 10, 11, 12, 13}; // Definování pinů pro konkrétní "pixel" (a, b, c, d, e, f, g, h)

const byte data[5][8] = {
//(a, b, c, d, e, f, g, h)
  {1, 1, 1, 1, 0, 1, 1, 0}, // A
  {0, 1, 1, 1, 0, 1, 1, 0}, // H
  {1, 1, 1, 1, 1, 1, 0, 0}, // O
  {0, 1, 1, 1, 1, 0, 0, 0}, // J
  {0, 0, 1, 1, 1, 1, 1, 0}, // default
};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(arr_position[i], OUTPUT);
    digitalWrite(arr_position[i], LOW);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(arr_segment[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    for (int n = 0; n < 8; n++) {
      digitalWrite(arr_segment[n], not data[i][n]);
    }
    digitalWrite(arr_position[i], HIGH);

    delay(1);

    digitalWrite(arr_position[i], LOW);
  }
} 
