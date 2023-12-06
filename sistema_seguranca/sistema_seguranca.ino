const int trigPin = 12;
const int echoPin = 11;

int speakerPin = 9;

long measureDistance() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2;
  delay(20);
  return distance;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  pinMode(10, OUTPUT);  // led

  pinMode(speakerPin, OUTPUT); // piezzo
}

void loop() {
  if (measureDistance() <= 20) {
    digitalWrite(10, HIGH);
    tone(speakerPin, 500);
  } else {
    digitalWrite(10, LOW);
    noTone(speakerPin);
  }
}


