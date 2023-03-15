#define encA1 2
#define encB1 31

int counter1;

void iqro1() {
  digitalRead(encB1) == 1 ? counter1++ : counter1--;
}

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(encA1), iqro1, RISING);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(counter1);
}
