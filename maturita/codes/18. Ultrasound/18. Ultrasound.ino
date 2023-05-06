int trigPin = 2;
int echoPin = 3;
int duration, distance_cm;

void setup(){
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance_cm = (duration / 29.155 ) / 2;
  Serial.println(distance_cm);
}

