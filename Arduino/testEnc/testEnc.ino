#define encA1 3
#define encB1 4

#define encZ 3

int counter1;
int rev;
void iqro1() {
  digitalRead(encB1) == 1 ? counter1++ : counter1--;
}

void bacaZ(){
  rev++;
}

void setup() {
  pinMode(6, OUTPUT);
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(encA1), iqro1, RISING);
//  attachInterrupt(digitalPinToInterrupt(encZ), bacaZ, RISING);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(6, 100);
  Serial.println(counter1);
}
