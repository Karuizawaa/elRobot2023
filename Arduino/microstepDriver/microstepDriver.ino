#define dirPin 9
#define stepPin 8
#define stepsPerRevolution 800 // sesuaikan dengan settingan SW1-SW3 pada modul motor driver
long sekarang;
void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);

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

int masuk;
void loop() {
  if(Serial.available()){
    masuk = Serial.parseInt();
  }
  toStep(masuk, 200);
}
