#define dirPin 3
#define stepPin 2
#define stepsPerRevolution 800 // sesuaikan dengan settingan SW1-SW3 pada modul motor driver
long sekarang;
void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}

void toStep(int langkah, int kecepatan) {
  while (sekarang != langkah) {

    if (langkah > sekarang) {
      digitalWrite(dirPin, LOW);
      sekarang++;
    }
    else {
      digitalWrite(dirPin, HIGH);
      sekarang--;
    }
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
  }
}
void loop() {
  toStep(800, 1000);
  if (sekarang == 800) {
    delay(2000);
    toStep(400, 2000);
    delay(2000);
  }
}
