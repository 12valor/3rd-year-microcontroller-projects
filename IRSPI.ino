// IR Sensor with 6 LEDs Test
// When obstacle detected → all LEDs ON
// When no obstacle → all LEDs OFF

int irPin = 2;                   // IR sensor output
int leds[] = {3, 4, 5, 6, 7, 8}; // 6 LEDs
int ledCount = 6;

void setup() {
  pinMode(irPin, INPUT);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  Serial.begin(9600);
  Serial.println("IR + 6 LED Test Initialized...");
}

void loop() {
  int irStatus = digitalRead(irPin);

  if (irStatus == LOW) {
    // Obstacle detected
    Serial.println("🚨 Obstacle Detected! LEDs ON");
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } else {
    // No obstacle
    Serial.println("✅ No Obstacle. LEDs OFF");
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], LOW);
    }
  }

  delay(200);
}
