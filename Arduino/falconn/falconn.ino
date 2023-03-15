#include "Servo.h"
Servo falcon;
int setPoint;
int rpm = 1000;
void setup() {
  // put your setup code here, to run once:
  falcon.attach(4);
}

void loop() {
  // put your main code here, to run repeatedly:
  setPoint = (-rpm / 13) + 1500;
  falcon.writeMicroseconds(setPoint);
}
