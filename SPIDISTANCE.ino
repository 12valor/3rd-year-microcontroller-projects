#define trigPin 2
#define echoPin 3

// 7 LEDs from pin 4 to 10
int leds[] = {4, 5, 6, 7, 8, 9, 10};
int ledCount = 7;

// Number of samples for smoothing
const int numSamples = 10;

float getSmoothedDistance() {
  float total = 0;

  for (int i = 0; i < numSamples; i++) {
    // Trigger ultrasonic pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure echo duration
    long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
    float distance = duration * 0.034 / 2; // convert to cm
    total += distance;

    delay(5); // short delay between samples
  }

  return total / numSamples; // average reading
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  float distance = getSmoothedDistance();

  Serial.print("Smoothed Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  int ledsOn = 0;

  if (distance > 50) {
    // All off beyond 50 cm
    ledsOn = 0;
  } 
  else {
    // Each 5 cm step lights one LED
    ledsOn = (50 - distance) / 5 + 1;
  }

  // Limit LEDs between 0 and ledCount
  ledsOn = constrain(ledsOn, 0, ledCount);

  // Turn LEDs on according to distance
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], i < ledsOn ? HIGH : LOW);
  }

  delay(100);
}
