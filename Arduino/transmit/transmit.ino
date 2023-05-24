#define POSM1 45
#define POSM2 135
#define POSM3 225
#define POSM4 315

#define RADIUSMTR 1
#define RADIUSBAN 1
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

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}
char tampung;
void loop() {
  kinematic(200,0,0,0);
}
