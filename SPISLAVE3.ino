#include <SPI.h>
#include <Servo.h>

#define SS_PIN 10
Servo sg90;

int initial_position;
int LDR1 = A2;
int LDR2 = A3;
int servopin = 5;

void setup() {
  pinMode(SS_PIN, INPUT);       // SPI hardware controls SS
  sg90.attach(servopin);
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);

  randomSeed(analogRead(0));
  initial_position = random(85, 91);
  sg90.write(initial_position);
  delay(1000);

  Serial.begin(9600);
  SPI.begin();
}

void loop() {
  if (digitalRead(SS_PIN) == LOW) { // active when selected
    int R1 = analogRead(LDR1);
    int R2 = analogRead(LDR2);

    Serial.print("LDR1: "); Serial.print(R1);
    Serial.print(" | LDR2: "); Serial.print(R2);
    Serial.print(" | Servo angle: "); Serial.println(initial_position);

    // Move servo based on thresholds
    if (R1 > 650 && R1 > R2) {
      initial_position--;
      if (initial_position < 0) initial_position = 0;
      Serial.println("Moving Left");
    } 
    else if (R2 > 250 && R2 > R1) {
      initial_position++;
      if (initial_position > 180) initial_position = 180;
      Serial.println("Moving Right");
    } 
    else {
      Serial.println("Servo idle");
    }

    sg90.write(initial_position);
    delay(250);
  }
}
