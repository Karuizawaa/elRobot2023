#define encA 3
#define encB 4
#define PWMM 9
#define CW   7
#define CCW  8

//#define KP 20
//#define KI 10

#define KP 14
#define KI 8

volatile long int encoder, lastEncoder;
unsigned long previousMillis = 0;
float setVel;

char packetBuffer[512];  // buffer to hold incoming packet,

unsigned long int prevT;
volatile float vFilt, vPrev, sum;
unsigned long tunggmillis;
// TODO: Declare something depending on your application
struct PG45 {
  char buffer[50];
  int counter;
  float vel;
} base;

void setup() {
  // Pins D9 and D10 - 31.4 kHz
//  TCCR1A = 0b00000001; // 8bit
//  TCCR1B = 0b00000001; // x1 phase correct

  Serial.begin(115200);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  
  pinMode(PWMM, OUTPUT);
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encA), readEnc, RISING);
}

void loop(){
//  Serial.println(encoder);
//  delay(1);
  updateVel();
  if(millis() - tunggmillis > 1){
//    motor(150);
    closedloopctl(base.vel);
    tunggmillis = millis();
  }
}
