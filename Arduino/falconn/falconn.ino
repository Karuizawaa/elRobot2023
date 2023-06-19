#include "Servo.h"
Servo falcon;
int setPoint;
int rpm = 1500;
void setup() {
  // put your setup code here, to run once:
  falcon.attach(9);
  Serial.begin(115200);
}

void loop() {

//  if (Serial.available()) {
//    rpm = Serial.parseInt();
//    Serial.println(rpm);
//  }
  falcon.writeMicroseconds(1656);
}
