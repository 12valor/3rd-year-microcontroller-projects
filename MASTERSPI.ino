#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_SLAVE1 7
#define SS_SLAVE2 8
#define SS_SLAVE3 9

#define BTN1 2
#define BTN2 3
#define BTN3 4
#define BTN4 5
#define BUZZER 6

int activeSlave = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(SS_SLAVE1, OUTPUT);
  pinMode(SS_SLAVE2, OUTPUT);
  pinMode(SS_SLAVE3, OUTPUT);

  digitalWrite(SS_SLAVE1, HIGH);
  digitalWrite(SS_SLAVE2, HIGH);
  digitalWrite(SS_SLAVE3, HIGH);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Master Ready");
  lcd.setCursor(0,1);
  lcd.print("No Mode Active");
}

void loop() {
  if (digitalRead(BTN1) == LOW) { activateSlave(1); delay(300); }
  else if (digitalRead(BTN2) == LOW) { activateSlave(2); delay(300); }
  else if (digitalRead(BTN3) == LOW) { activateSlave(3); delay(300); }
  else if (digitalRead(BTN4) == LOW) { deactivateAll(); delay(300); }
}

void activateSlave(int slave) {
  deactivateAll(); // ensure only one active
  switch(slave){
    case 1: 
      digitalWrite(SS_SLAVE1, LOW); activeSlave = 1; Serial.println("Slave 1 active");
      lcd.setCursor(0,1); lcd.print("Ultrasonic Mode "); break;
    case 2: 
      digitalWrite(SS_SLAVE2, LOW); activeSlave = 2; Serial.println("Slave 2 active");
      lcd.setCursor(0,1); lcd.print("IR LED Mode     "); break;
    case 3: 
      digitalWrite(SS_SLAVE3, LOW); activeSlave = 3; Serial.println("Slave 3 active");
      lcd.setCursor(0,1); lcd.print("Solar Tracker   "); break;
  }
  beep(1); // 1 beep on activation
}

void deactivateAll() {
  digitalWrite(SS_SLAVE1, HIGH);
  digitalWrite(SS_SLAVE2, HIGH);
  digitalWrite(SS_SLAVE3, HIGH);

  if(activeSlave != 0){
    Serial.print("Slave "); Serial.print(activeSlave); Serial.println(" deactivated.");
    activeSlave = 0;
    lcd.setCursor(0,1); lcd.print("No Mode Active  ");
    beep(2); // 2 beeps on deactivation
  }
}

void beep(int times){
  for(int i=0; i<times; i++){
    digitalWrite(BUZZER,HIGH);
    delay(150);
    digitalWrite(BUZZER,LOW);
    delay(150);
  }
}
