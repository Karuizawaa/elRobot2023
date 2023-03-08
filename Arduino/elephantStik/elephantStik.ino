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
#define RADIUSBAN 0.136/2
#define KBAN 2*M_PI*RADIUSBAN

#define PWMMAX 200

#define KP1 10
#define KI1 8
#define encA1 2
#define encB1 44
#define pwmM1 5
#define cwM1  23
#define ccwM1 25
#define POSM1 45

#define KP2 10
#define KI2 8
#define encA2 3
#define encB2 22
#define pwmM2 6
#define cwM2  27
#define ccwM2 29
#define POSM2 135

#define KP3 10
#define KI3 8
#define encA3 18
#define encB3 26
#define pwmM3 7
#define cwM3  31
#define ccwM3 33
#define POSM3 225

#define KP4 10
#define KI4 8
#define encA4 20
#define encB4 28
#define pwmM4 8
#define cwM4  35
#define ccwM4 37
#define POSM4 315

#define KPx 2
#define KIx 0

#define KPy 2
#define KIy 0

#define KPt 1.0
#define KIt 0

#define PPR 134.4
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


struct gy25 {
  char buffer[50];
  int counter;
  float heading;
} cmps;


void setup() {
  Serial.begin(115200);
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

  //  nh.initNode();
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
  //  nh.subscribe(subsCase);
}


void loop() {
  // auto
//  nh.spinOnce();
Serial.print(enc1);Serial.print("\t");Serial.print(enc2);Serial.print("\t");Serial.print(enc3);Serial.print("\t");Serial.println(enc4);
  updateCMPS();
//  Serial.println(cmps.heading);/
//  motor4(-100);
  calculatePos();
//  Serial.print(x);Serial.print("\t");Serial.println(y);
//  kinematic(-4,0,0);
//  setPos(-4, 0, 0);
//  if (caseRobot == 0) {
//    setPos(0, 0, 0);
//  }
//  else if (caseRobot == 1) {
//    setPos(0, -10.2, 0);
//  }
//  else if (caseRobot == 3) {
//    setPos(-4, -5.2, 0);
//  }
//  else if (caseRobot == 4) {
//    setPos(-4, -5.2, 90);
//  }
//  else if (caseRobot == 5) {
//    setPos(-4, -5.2, 0);
//  }


  calculatePos();
  if (Serial.available()) {
    bacaSer = Serial.read();
  }
  if (bacaSer == 'a') {
    setPos(0, -10.2, 0);
  }
  if (bacaSer == 'b') {
    setPos(-4, -5.2, 0);
  }
  if (bacaSer == 'c') {
    setPos(-4, -5.2, 90);
  }
  if (bacaSer == 'd') {
    setPos(-4, -5.2, 0);
  }
  if (bacaSer == 'e') {
    setPos(0, 0, 0);
  }
}
