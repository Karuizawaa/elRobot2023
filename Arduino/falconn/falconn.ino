#include "Servo.h"
Servo falcon;
int setPoint;
int rpm = 0;
void setup() {
  // put your setup code here, to run once:
  falcon.attach(12);
  Serial.begin(115200);
}

void loop() {

  if (Serial.available()) {
    rpm = Serial.parseInt();
    Serial.println(rpm);
  }
  // put your main code here, to run repeatedly:
  setPoint = (rpm / 13) + 1500;
  falcon.writeMicroseconds(setPoint);
}
