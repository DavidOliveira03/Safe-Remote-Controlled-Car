#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3);  //tx e rx

struct PacketData {
  byte lxAxisValue;
  byte lyAxisValue;
  byte rxAxisValue;
  byte ryAxisValue;
};
PacketData data;

//motor direito
int enableRightMotor = 5;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

//motor esquerdo
int enableLeftMotor = 6;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

unsigned long lastRecvTime = 0;
/*
const int trigPin = 11;
const int echoPin = 13;

int speakerPin = 4;

int ledPin = 12;

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
*/
void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
/*
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledPin, OUTPUT);  // led

  pinMode(speakerPin, OUTPUT); // piezzo
*/
  rotateMotor(0, 0);

  btSerial.begin(38400);
}

void loop() {
  String dataString;
  if (btSerial.available()) {
    dataString = btSerial.readStringUntil('\n');
    sscanf(dataString.c_str(), "%d,%d,%d,%d", &data.lxAxisValue, &data.lyAxisValue, &data.rxAxisValue, &data.ryAxisValue);
    int throttle = map(data.lyAxisValue, 254, 0, -255, 255);  //esq. "joystick" - y axis - frente/trás
    int steering = map(data.rxAxisValue, 0, 254, -255, 255);  //dir. "joystick" - x axis - esquerda/direita
    int motorDirection = 1;

    if (throttle < 0)  //marcha-atrás
    {
      motorDirection = -1;
    }

    int rightMotorSpeed, leftMotorSpeed;
    rightMotorSpeed = abs(throttle) - steering;
    leftMotorSpeed = abs(throttle) + steering;
    rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);
    leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);

    rotateMotor(rightMotorSpeed * motorDirection, leftMotorSpeed * motorDirection);
    lastRecvTime = millis();
/*
    int distance = measureDistance();
    if (distance <= 10) {
      digitalWrite(ledPin, HIGH);
      tone(speakerPin, 400);
    } else {
      digitalWrite(ledPin, LOW);
      noTone(speakerPin);
    }
*/
  } else {
    unsigned long now = millis();
    if (now - lastRecvTime > 1000)  //sinal perdido após 1 segundo, "reset" ao motor para parar
    {
      rotateMotor(0, 0);
    }
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}