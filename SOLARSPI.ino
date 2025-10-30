  // Techatronic.com
#include <Servo.h>      // including the library of servo motor 
Servo sg90;             

int initial_position;   // will be randomly set between 85–90
int LDR1 = A2;          // connect The LDR1 on Pin A2
int LDR2 = A3;          // connect The LDR2 on Pin A3
int error = 5;         
int servopin = 5;       // Servo connected to PWM pin (e.g., D5)

void setup() 
{ 
  Serial.begin(9600);          
  sg90.attach(servopin);  
  pinMode(LDR1, INPUT);   
  pinMode(LDR2, INPUT);

  // ✅ Randomize initial position between 85–90
  randomSeed(analogRead(0));  
  initial_position = random(85, 91);   // 85 to 90 inclusive
  
  sg90.write(initial_position);   
  delay(1000);           

  Serial.println("System Initialized...");
  Serial.print("Servo initialized at angle: ");
  Serial.println(initial_position);
}  
 
void loop() 
{ 
  int R1 = analogRead(LDR1); // read LDR 1
  int R2 = analogRead(LDR2); // read LDR 2

  // ✅ Serial print readings
  Serial.print("LDR1: "); Serial.print(R1);
  Serial.print(" | LDR2: "); Serial.print(R2);
  Serial.print(" | Servo angle: "); Serial.println(initial_position);

  delay(100);

  int diff = abs(R1 - R2);   

  // ✅ Condition 1: Both LDRs below 800 → no movement
  if (R1 < 800 && R2 < 800) {
    Serial.println("⚠️ Low light - servo idle");
    return;
  }

  // ✅ Condition 2: Both readings are strong, but difference small → stable
  if (diff <= error) {
    Serial.println("☀️ Balanced light - no movement");
    return;
  }

  // ✅ Condition 3: One LDR > other AND that LDR > 800 → move
  if (R1 > R2 && R1 > 800) {
    initial_position--;
    if (initial_position < 0) initial_position = 0;
    Serial.println("⬅️ Moving Left (LDR1 brighter)");
  }
  else if (R2 > R1 && R2 > 800) {
    initial_position++;
    if (initial_position > 180) initial_position = 180;
    Serial.println("➡️ Moving Right (LDR2 brighter)");
  }

  sg90.write(initial_position); 
  delay(250);
}
