/*****************************************************************************
   Saturday, 11 Feb 2023

   Koding base Robot Gajah
   Odometry Absolute
   PID Posisi Absolute
   rosserial

   maintainer : Aldi Roby Syafriansyah
   email      : aldirobyy@gmail.com / aldisyafriansyah@protonmail.com

*****************************************************************************/
#include "ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int16.h"
#include "std_msgs/UInt8.h"

bool kiri, kanan, bawah, atas, buttonSq, buttonX, buttonO, buttonTr, buttonTouch, l1, r1;
float leftStickY, leftStickX, rightStickY, rightStickX, l2, r2;
int8_t vX, vY;
uint8_t caseRobot;
void petak(const std_msgs::Bool& btpetak) {
  buttonSq = btpetak.data;
}
void kali(const std_msgs::Bool& btkali) {
  buttonX = btkali.data;
  if (buttonX) {
    //    Serial2.write('a');
  }
}
void bulet(const std_msgs::Bool& btbulet) {
  buttonO = btbulet.data;
  if (buttonO) {
    //    Serial2.write('b');
  }
}
void lupis(const std_msgs::Bool& btlupis) {
  buttonTr = btlupis.data;
}
void lsat(const std_msgs::Bool& btlsat) {
  l1 = btlsat.data;
}
void rsat(const std_msgs::Bool& btrsat) {
  r1 = btrsat.data;
}
void left(const std_msgs::Bool& btarrow) {
  kiri = btarrow.data;
  vX = kiri * -3;
}
void right(const std_msgs::Bool& btarrow) {
  kanan = btarrow.data;
  vX = kanan * 3;
}
void up(const std_msgs::Bool& btarrow) {
  atas = btarrow.data;
  vY = atas * 3;
}
void down(const std_msgs::Bool& btarrow) {
  bawah = btarrow.data;
  vY = bawah * -3;
}
void rdua(const std_msgs::Float32& trigg) {
  r2 = trigg.data;
  r2 = -(r2 - 1) * 1;
}
void ldua(const std_msgs::Float32& trigg) {
  l2 = trigg.data;
  l2 = -(l2 - 1) * 1;
}
void lx(const std_msgs::Float32& trigg) {
  leftStickX = trigg.data;
  leftStickX = -leftStickX * 3;
}
void ly(const std_msgs::Float32& trigg) {
  leftStickY = trigg.data;
  leftStickY = leftStickY * 3;
}
void recCase(const std_msgs::UInt8& caseRec) {
  caseRobot = caseRec.data;
}
ros::NodeHandle nh;

ros::Subscriber<std_msgs::Bool> subsq ("petak", petak);
ros::Subscriber<std_msgs::Bool> subX ("kali", kali);
ros::Subscriber<std_msgs::Bool> subO ("bulet", bulet);
ros::Subscriber<std_msgs::Bool> subTr ("lupis", lupis);
ros::Subscriber<std_msgs::Bool> sublsat ("lsatu", lsat);
ros::Subscriber<std_msgs::Bool> subrsat ("rsatu", rsat);
ros::Subscriber<std_msgs::Bool> subleft ("left", left);
ros::Subscriber<std_msgs::Bool> subright ("right", right);
ros::Subscriber<std_msgs::Bool> subup ("up", up);
ros::Subscriber<std_msgs::Bool> subdown ("down", down);
ros::Subscriber<std_msgs::Float32> sublX ("lx", lx);
ros::Subscriber<std_msgs::Float32> sublY ("ly", ly);
ros::Subscriber<std_msgs::Float32> subl2 ("ldua", ldua);
ros::Subscriber<std_msgs::Float32> subr2 ("rdua", rdua);
ros::Subscriber<std_msgs::UInt8> subsCase ("case", recCase);

std_msgs::Int16 hadap;
ros::Publisher IMU("head", &hadap);



#define RADIUSMTR 0.35145 //satuan meter
#define RADIUSBAN 0.1/2
#define KBAN 2*M_PI*RADIUSBAN

#define PWMMAX 200

//MOTOR 1
#define KP1  14
#define KI1 8
#define encA1 2
#define encB1 31
#define pwmM1 6
#define cwM1  37
#define ccwM1 39
#define POSM1   45

//MOTOR 2
#define KP2 14
#define KI2 8
#define encA2 3
#define encB2 23
#define pwmM2 5
#define cwM2  35
#define ccwM2 33
#define POSM2   135

//MOTOR 3
#define KP3 14
#define KI3 8
#define encA3 18
#define encB3 17
#define pwmM3 4
#define cwM3  49
#define ccwM3 47
#define POSM3 225

//MOTOR 4
#define KP4 14
#define KI4 8
#define encA4 19
#define encB4 41
#define pwmM4 7
#define cwM4  22 
#define ccwM4 24
#define POSM4 315

#define LIM1 9 // belum fix
#define LIM2 10
#define LIM3 11
#define LIM4 12
#define LIM5 13
#define LIM6 52
#define LIM7 50
#define LIM8 48
#define LIM9 48
#define LIM10 48


#define KPx 2
#define KIx 0

#define KPy 2
#define KIy 0

#define KPt 1.0
#define KIt 0

#define PPR 3840
#define RADIUSENC 0.004 //satuan meter
#define KENCODER 2 * M_PI * 0.002

volatile long int enc1, enc2, enc3, enc4, lastEnc1, lastEnc2, lastEnc3, lastEnc4;

volatile float radps1, radps2, radps3, radps4;
volatile float PID1, PID2, PID3, PID4, err1, err2, err3, err4, lastErr1, lastErr2, lastErr3, lastErr4, sum1, sum2, sum3, sum4;
float setradPS1, setradPS2, setradPS3, setradPS4;

float setX, setY, setT;
volatile float errX, errY, errT, PIDx, PIDy, PIDt, sumX, sumY, sumT;
volatile long int last1, last2, last3, last4;

volatile unsigned long prevT, prevT1, prevT2, prevT3, prevT4;
float absY, absX, actTheta;

volatile float v1Filt, v2Filt, v3Filt, v4Filt;
volatile float v1Prev, v2Prev, v3Prev, v4Prev;

float XSmoothed, YSmoothed, TSmoothed;
float XPrev, YPrev, TPrev;
unsigned long waitSmooth;

char bacaSer;
bool pnu1, pnu2, pnu3, pnu4;
float x, y;
unsigned long curr;
int x_temp, y_temp;


struct gy25 {
  char buffer[50];
  int counter;
  float heading;
} cmps;

void kalibrasi(){
  Serial3.begin(115200);

  Serial.println("mulai kalibret");

  delay(3000);

  Serial3.write(0xA5);
  Serial3.write(0x54);

  delay(1000); // Jeda sebelum kalibrasi heading

  // Kalibrasi Heading
  Serial3.write(0xA5);
  Serial3.write(0x55);

  delay(100); // Jeda sebelum konfigurasi output

  // Output ASCII
  Serial3.write(0xA5);
  Serial3.write(0x53);

  delay(100); // Jeda sebentar

  Serial.println("selesai kalibret");
}

void setup() {
  Serial.begin(115200);
//  kalibrasi();

  pinMode(13, OUTPUT);
  pinMode(encA1, INPUT);
  pinMode(encB1, INPUT);

  pinMode(encA2, INPUT);
  pinMode(encB2, INPUT);

  pinMode(encA3, INPUT);
  pinMode(encB3, INPUT);

  pinMode(encA4, INPUT);
  pinMode(encB4, INPUT);

  attachInterrupt(digitalPinToInterrupt(encA1), readEnc1, RISING);
  attachInterrupt(digitalPinToInterrupt(encA2), readEnc2, RISING);
  attachInterrupt(digitalPinToInterrupt(encA3), readEnc3, RISING);
  attachInterrupt(digitalPinToInterrupt(encA4), readEnc4, RISING);

  pinMode(pwmM1, OUTPUT);
  pinMode(cwM1, OUTPUT);
  pinMode(ccwM1, OUTPUT);

  pinMode(pwmM2, OUTPUT);
  pinMode(cwM2, OUTPUT);
  pinMode(ccwM2, OUTPUT);

  pinMode(pwmM3, OUTPUT);
  pinMode(cwM3, OUTPUT);
  pinMode(ccwM3, OUTPUT);

  pinMode(pwmM4, OUTPUT);
  pinMode(cwM4, OUTPUT);
  pinMode(ccwM4, OUTPUT);

  pinMode(LIM1, INPUT_PULLUP);
  pinMode(LIM2, INPUT_PULLUP);
  pinMode(LIM3, INPUT_PULLUP);
  pinMode(LIM4, INPUT_PULLUP);
  pinMode(LIM5, INPUT_PULLUP);
  pinMode(LIM6, INPUT_PULLUP);
  pinMode(LIM7, INPUT_PULLUP);
  pinMode(LIM8, INPUT_PULLUP);
  pinMode(LIM9, INPUT_PULLUP);
  pinMode(LIM10, INPUT_PULLUP);

//      nh.initNode();
  //  nh.advertise(IMU);
  //      nh.subscribe(subsq);
  //      nh.subscribe(subX);
  //      nh.subscribe(subO);
  //      nh.subscribe(subTr);
  //      nh.subscribe(subup);
  //      nh.subscribe(subleft);
  //      nh.subscribe(subright);
  //      nh.subscribe(subdown);
  //      nh.subscribe(sublX);
  //      nh.subscribe(sublY);
  //      nh.subscribe(subl2);
  //      nh.subscribe(subr2);
//      nh.subscribe(subsCase);
}


void loop() {
  // auto
    nh.spinOnce();
//    Serial.print(digitalRead(LIM1)); Serial.print(" "); Serial.print(digitalRead(LIM2)); Serial.print(" "); Serial.print(digitalRead(LIM3)); Serial.print(" "); Serial.print(digitalRead(LIM4)); Serial.print(" "); Serial.print(digitalRead(LIM5)); Serial.print(" "); Serial.println(digitalRead(LIM6));
//    Serial.print(enc1);Serial.print("\t");Serial.print(enc2);Serial.print("\t");Serial.print(enc3);Serial.print("\t");Serial.println(enc4);
  updateCMPS();
  calculatePos();
  Serial.print(x); Serial.print("\t"); Serial.println(y);

  //ambil ring kiri
  if (caseRobot == 1){
    if (y > -9.2) {
      setPos(0, -10.0, 0);
    }
    if (y < -9.2) {
      sum1 = 0;
      sum2 = 0;
      sum3 = 0;
      sum4 = 0;
      kinematic(0,0,0,0,0);
      waitMillis(1000);

      //nyender fence belakang
      while (!(digitalRead(LIM4) == 0 && digitalRead(LIM5) == 0)) {
        calculatePos();
        nh.spinOnce();
        kinematic(2.5, 0, 0, 0, 1);
        Serial.println("nyender fence blakang");
        x_temp = x;
      }
      kinematic(0, 0, 0, 0, 0);
      waitMillis(1500);
      
      //nyender fence samping
      while (!(digitalRead(LIM3) == 0 && digitalRead(LIM2) == 0)) {
        calculatePos();
        nh.spinOnce();
        kinematic(0, -3, 0, 0, 1);
      }
      sum1 = 0;
      sum2 = 0;
      sum3 = 0;
      sum4 = 0;
      XSmoothed = x;
      YSmoothed = y;
      XPrev = x;
      YPrev = y;
      x_temp = x;
      y_temp = y;
      while (caseRobot == 1) {
        calculatePos();
        kinematic(0, 0, 0, 0, 0);
        nh.spinOnce();
      }
    }
  }
  if(caseRobot == 2){
    if(x > x_temp - 3){
      setPos(x_temp - 3, y_temp + 3, 45);
    }
  }

  //ambil ring kanan
  if (caseRobot == 8) {
    if (y < 11) {
      setPos(0, 11.8, 178.9);
    }
    if (y > 11 ) {
      sum1 = 0;
      sum2 = 0;
      sum3 = 0;
      sum4 = 0;
      kinematic(0,0,0,0,0);
      waitMillis(1000);

      //nyender fence belakang
      while (!(digitalRead(LIM7) == 0 && digitalRead(LIM8) == 0)) {
        calculatePos();
        nh.spinOnce();
        kinematic(-2.5, 0, 0, 0, 1);
        x_temp = x;
      }
      kinematic(0, 0, 0, 0, 0);
      waitMillis(1500);

      //nyender fence samping
      while (!(digitalRead(LIM2) == 0 && digitalRead(LIM3) == 0)) {
        calculatePos();
        nh.spinOnce();
        kinematic(0, -3, 0, 0, 1);
      }
      sum1 = 0;
      sum2 = 0;
      sum3 = 0;
      sum4 = 0;
      XSmoothed = x;
      YSmoothed = y;
      XPrev = x;
      YPrev = y;
      while (caseRobot == 8) {
        kinematic(0, 0, 0, 0, 0);
        nh.spinOnce();
      }
    }


  }  
}

//void loop(){
////  motor4(-50);                                            
//  Serial.print(digitalRead(LIM1)); Serial.print(" "); Serial.print(digitalRead(LIM2)); Serial.print(" "); Serial.print(digitalRead(LIM3)); Serial.print(" "); Serial.print(digitalRead(LIM4)); Serial.print(" "); Serial.print(digitalRead(LIM5)); Serial.print(" "); Serial.print(digitalRead(LIM6)); Serial.print(" "); Serial.print(digitalRead(LIM7)); Serial.print(" "); Serial.print(digitalRead(LIM8)); Serial.print(" "); Serial.print(digitalRead(LIM9)); Serial.print(" "); Serial.println(digitalRead(LIM10));
////Serial.print(enc1);Serial.print("\t");Serial.print(enc2);Serial.print("\t");Serial.print(enc3);Serial.print("\t");Serial.println(enc4);
////  setradPS4 = 2*M_PI * 4;
////  PID();
////  Serial.println(v1Filt);
////  Serial.print(setradPS4); Serial.print(" "); Serial.println(v4Filt);
////Serial.print(enc1);Serial.print("\t");Serial.print(enc2);Serial.print("\t");Serial.print(enc3);Serial.print("\t");Serial.println(enc4);
////  motor3(100);
//}
