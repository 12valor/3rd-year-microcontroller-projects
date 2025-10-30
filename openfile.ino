const int buttonPin = 6;  
int lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);  // COM8
}

void loop() {
  int currentState = digitalRead(buttonPin);

  if (lastState == HIGH && currentState == LOW) {
    Serial.println("OPEN_FILE");
    delay(300); // debounce
  }

  lastState = currentState;
}
