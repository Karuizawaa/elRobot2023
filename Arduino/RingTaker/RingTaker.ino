#include "ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/UInt8.h"
#include "Servo.h"

bool buttonX, buttonO, r1;

#define KP1 150
#define KI1 0
#define KD1 0

#define KP2 9
#define KI2 0
#define KD2 0

//motor transfer ke launcher
#define encA1 2
#define encB1 44
#define PWMM1 5
#define CW1   31
#define CCW1  33
#define LSDPN 25

//PG28 Lifter
#define encA2 3
#define encB2 24
#define PWMM2 6
#define CW2   35
#define CCW2  37
#define LSWUP 29
#define LSWDN 27

#define encA3 3
#define encB3 24
#define PWMM3 7
#define CW3   39
#define CCW3  41

#define encA4 3
#define encB4 24
#define PWMM4 8
#define CW4   43
#define CCW4  45

//motor launcher
#define PWMM5 4
#define CW5   47
#define CCW5  49

#define PN1 9
#define PN2 10
#define PN3 11

int counter1, counter2;
int waitSmooth;

float falconSmoothed;
float falconPrev;

uint8_t bacaSerial[10];
uint8_t caseRobot;

unsigned long curr;

char mode;

unsigned long prevT = 0, waitGripper;
float setPoint;
volatile int err1, err2, err3, lastErr1, lastErr2, lastErr3, sum1, sum2, sum3, PID1, PID2, PID3;

void kali(const std_msgs::Bool& btkali) {
  buttonX = btkali.data;
  if (buttonX) {
    mode = 'a';
  }
}
void bulet(const std_msgs::Bool& btbulet) {
  buttonO = btbulet.data;
  if (buttonO) {
    mode = 'b';
  }
}

void recCase(const std_msgs::UInt8& rec) {
  caseRobot = rec.data;
}

void rsat(const std_msgs::Bool& btrsat) {
  r1 = btrsat.data;
}

ros::NodeHandle nh;

bool sekali;
bool modeKalibret = false;

Servo falcon;

//ros::Subscriber<std_msgs::Bool> subX ("kali", kali);
//ros::Subscriber<std_msgs::Bool> subO ("bulet", bulet);
ros::Subscriber<std_msgs::UInt8> subsCase ("case", recCase);
ros::Subscriber<std_msgs::Bool> sublsat ("rsatu", rsat);

void setup() {
  falcon.attach(4);
  pinMode(PN1, OUTPUT);
  pinMode(PN2, OUTPUT);
  pinMode(PN3, OUTPUT);


  pinMode(encA1, INPUT);
  pinMode(encB1, INPUT);
  pinMode(encA2, INPUT);
  pinMode(encB2, INPUT);

  pinMode(LSWUP, INPUT_PULLUP);
  pinMode(LSWDN, INPUT_PULLUP);
  pinMode(LSDPN, INPUT_PULLUP);

  pinMode(PWMM1, OUTPUT);
  pinMode(CW1, OUTPUT);
  pinMode(CCW1, OUTPUT);
  pinMode(PWMM2, OUTPUT);
  pinMode(CW2, OUTPUT);
  pinMode(CCW2, OUTPUT);
  pinMode(PWMM3, OUTPUT);
  pinMode(CW3, OUTPUT);
  pinMode(CCW3, OUTPUT);
  pinMode(PWMM4, OUTPUT);
  pinMode(CW4, OUTPUT);
  pinMode(CCW4, OUTPUT);
  pinMode(PWMM5, OUTPUT);
  pinMode(CW5, OUTPUT);
  pinMode(CCW5, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  //  Serial2.begin(115200);
  attachInterrupt(digitalPinToInterrupt(encA1), iqro1, RISING);
  attachInterrupt(digitalPinToInterrupt(encA2), iqro2, RISING);
  //  nh.initNode();
  //    nh.subscribe(subX);
  //    nh.subscribe(subO);
  //  nh.subscribe(subsCase);
  //  nh.subscribe(sublsat);

  //  nh.spinOnce();
  digitalWrite(PN1, HIGH); //lifter dibawah
  digitalWrite(PN2, HIGH); //slider launcherkedepan
  digitalWrite(PN3, HIGH);

  sekali = true;

  //  calibrate();
}
int wkwk;

void loop() {
  if (Serial.available()) {
        wkwk = Serial.parseInt();
//    wkwk = Serial.read();
  }

  //  digitalWrite(PN1, !digitalRead(PN1));
  //  waitMillis(1500);
  //  digitalWrite(PN2, !digitalRead(PN2));
  //  waitMillis(1500);
  //  digitalWrite(PN3, !digitalRead(PN3));
  //  waitMillis(1500);
  //  digitalWrite(PN4, !digitalRead(PN4));
  //  waitMillis(1500);
  //  Serial.println(wkwk);
  motor1(250);
  motoFalcon(wkwk);
  ////  nh.spinOnce();
  //  if(caseRobot == 2){
  //    digitalWrite(PN1, LOW); //lifter keatas
  //    waitMillis(1000);
  //    digitalWrite(PN2, LOW); //slider kebelakang
  //    waitMillis(1000);
  //    digitalWrite(PN1, HIGH); //lifter turun kembali
  //
  //    while(caseRobot == 2){
  //      nh.spinOnce();
  //    }
  //  }
  //  if(caseRobot == 3){
  //    digitalWrite(PN1, LOW);
  //    digitalWrite(PN2, LOW);
  //    //falcon steady and base ngeker
  //    //launching
  //    if(r1 == 1) motor1(200);
  //    else motor1(0);
  //  }
}
