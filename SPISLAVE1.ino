#include <SPI.h>

#define SS_PIN 10 // must match master’s SS pin for this slave
#define trigPin 2
#define echoPin 3

int leds[] = {4, 5, 6, 7, 8, 9}; // 6 LEDs
int ledCount = 6;

const int numSamples = 10;

float getSmoothedDistance() {
  float total = 0;
  for (int i = 0; i < numSamples; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);
    float distance = duration * 0.034 / 2;
    total += distance;
    delay(5);
  }
  return total / numSamples;
}

void setup() {
  pinMode(SS_PIN, INPUT); // SPI hardware controls SS
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < ledCount; i++) pinMode(leds[i], OUTPUT);
  Serial.begin(9600);
  SPI.begin();
}

void loop() {
  if (digitalRead(SS_PIN) == LOW) { // only active when selected
    float distance = getSmoothedDistance();
    Serial.print("Smoothed Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    int ledsOn;
    if (distance <= 15) ledsOn = ledCount;
    else ledsOn = ledCount - ((distance - 15) / 10);

    ledsOn = constrain(ledsOn, 0, ledCount);

    for (int i = 0; i < ledCount; i++)
      digitalWrite(leds[i], i < ledsOn ? HIGH : LOW);

    delay(100);
  } else {
    // Slave not selected → turn off all LEDs
    for (int i = 0; i < ledCount; i++)
      digitalWrite(leds[i], LOW);
  }
}
