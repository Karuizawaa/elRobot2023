#include "Servo.h"

Servo B3;

int sudut;
int writems;
void servo(int sudut){
  int writems = (400.0 * (float)sudut / 27.0) + 500.0;
  B3.writeMicroseconds(writems);
}

void setup() {
  Serial.begin(9600);
  B3.attach(6);

}

void loop() {
  servo(35);
}
