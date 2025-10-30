#include <SPI.h>

#define SS_PIN 10 // must match master’s SS pin for this slave
#define IR_PIN 2
int leds[] = {3, 4, 5, 6, 7, 8}; // 6 LEDs
int ledCount = 6;

void setup() {
  pinMode(SS_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  for (int i = 0; i < ledCount; i++) pinMode(leds[i], OUTPUT);
  Serial.begin(9600);
  SPI.begin();
}

void loop() {
  if (digitalRead(SS_PIN) == LOW) { 
    // Slave is selected
    int state = digitalRead(IR_PIN);
    if (state == LOW) { // obstacle detected
      Serial.println("Obstacle detected!");
      for (int i = 0; i < ledCount; i++) digitalWrite(leds[i], HIGH);
    } else {
      for (int i = 0; i < ledCount; i++) digitalWrite(leds[i], LOW);
    }
  } else {
    // Slave not selected → turn off all LEDs immediately
    for (int i = 0; i < ledCount; i++) digitalWrite(leds[i], LOW);
  }

  delay(50); // smaller delay for more immediate response
}
