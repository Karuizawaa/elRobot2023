//tes mekanisme atas
#include <Servo.h>

Servo B3;



#define PUL 4
#define DIR 5

#define pwmM1 6
#define cwM1  37
#define ccwM1 39
#define PWMMAX 200

#define LIMF 2
#define LIMB 1

long sekarang;


void setup() {
  Serial.begin(115200);
  pinMode(LIMF, INPUT_PULLUP);
  pinMode(LIMB, INPUT_PULLUP);

  pinMode(pwmM1, OUTPUT);
  pinMode(cwM1, OUTPUT);
  pinMode(ccwM1, OUTPUT);

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);

  kalibrasi();

}

void loop() {
  if(Serial.available()){
    //mundur kebelakang sampai limit dan servo keatas
    do{
      motor1(-100);
      servo(90);
    }while(digitalRead(LIMB) == 1);
    motor1(0);
    //servo full turun
    //kedepan sampai limit
  }
  // put your main code here, to run repeatedly:

}
