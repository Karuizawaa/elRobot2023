#define POSM1 45
#define POSM2 135
#define POSM3 225
#define POSM4 315

#define RADIUSMTR 0.1 //meter
#define RADIUSBAN 0.243



float toRad(float degree) {
  return degree * M_PI / 180;
}

void kinematic(float vX, float vY, float theta, float heading) {
    float setradPS1 = (-sin(toRad(POSM1 + heading)) * vX + cos(toRad(POSM1 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
    float setradPS2 = (-sin(toRad(POSM2 + heading)) * vX + cos(toRad(POSM2 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
    float setradPS3 = (-sin(toRad(POSM3 + heading)) * vX + cos(toRad(POSM3 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
    float setradPS4 = (-sin(toRad(POSM4 + heading)) * vX + cos(toRad(POSM4 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
    Serial.print('!');Serial.println(setradPS1);
    Serial.print('@');Serial.println(setradPS2);
    Serial.print('#');Serial.println(setradPS3);
    Serial.print('$');Serial.println(setradPS4);
}
void updateCMPS() {
  char tmp; // Variabel temporary
  while (Serial3.available()) {
    tmp = Serial3.read();
    cmps.buffer[cmps.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      cmps.buffer[cmps.counter] = 0; // Karakter terminator
      cmps.heading = atof(strtok(cmps.buffer + 5, ",")); // Langkah 2-4
      cmps.headInt = (int)cmps.heading;
      cmps.counter = 0;
    }
  }
}
