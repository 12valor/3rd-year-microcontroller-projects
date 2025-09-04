#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11
#define RELAY_PIN 8
#define RELAY_ACTIVE_LOW false   // set to false if you use active-HIGH relay

#define TEMP_THRESHOLD 35
#define READ_INTERVAL_MS 1000

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);

  // Set relay OFF at start
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(RELAY_PIN, HIGH); // OFF for active-LOW
  } else {
    digitalWrite(RELAY_PIN, LOW);  // OFF for active-HIGH
  }
}

void loop() {
  static unsigned long lastRead = 0;
  unsigned long now = millis();
  if (now - lastRead < READ_INTERVAL_MS) return;
  lastRead = now;

  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("DHT read failed");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" °C");

  bool relayOn = (temp >= TEMP_THRESHOLD);

  if (relayOn) {
    if (RELAY_ACTIVE_LOW) digitalWrite(RELAY_PIN, LOW);
    else digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Relay: ON");
  } else {
    if (RELAY_ACTIVE_LOW) digitalWrite(RELAY_PIN, HIGH);
    else digitalWrite(RELAY_PIN, LOW);
    Serial.println("Relay: OFF");
  }
}
