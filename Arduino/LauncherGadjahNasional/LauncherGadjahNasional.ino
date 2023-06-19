/* Bismillah juara 1
 * 
 * KRAI - BARELANG V
 * Kendali launcher
 */
 

#include <ADS1X15.h>
#include <Servo.h>
#include <EEPROM.h>

#define SWCW  10
#define SWCCW 11
#define SAVEPOS 12

#define PWMM 6
#define CW   7
#define CCW  8
#define PWMMAX 80

#define KP 0.3

#define TOTALTIANG 5

#define HADAPDEPAN EEPROM.read(4094)<<8|EEPROM.read(4095)
#define NILAIMAX EEPROM.read(4092)<< 8|EEPROM.read(4093)

#define NILAIMIN 100

ADS1115 ADS(0x48);

unsigned long previousMillis = 0;
int setVel;

unsigned long int prevT;
volatile float vFilt, vPrev, sum;
unsigned long tunggmillis;

struct KRUN {
  char buffer[50];
  int counter;
  int pwm;
  int pos;
  bool mode;
} base;

void setup() 
{
  // Pins D5 and D6 - 31.4 kHz
//  TCCR0B = 0b00000001; // x1
//  TCCR0A = 0b00000001; // phase correct
  pinMode(SWCW, INPUT_PULLUP);
  pinMode(SWCCW, INPUT_PULLUP);
  pinMode(SAVEPOS, INPUT_PULLUP);

  pinMode(PWMM, OUTPUT);
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  
  Serial.begin(115200);
  ADS.begin();
  base.mode = false;
  base.pos = 0;
  
//  cariDepan();
//  cariTiang();
}


void loop() 
{
  ADS.setGain(0);
//  int16_t val_0 = ADS.readADC(0);  
//  Serial.print("\tAnalog0: "); Serial.println(val_0);
  updatePOS();
  
  if(base.mode)motor(base.pwm);
  else closedloopctl(gotoTiang(base.pos));
//  closedloopctl(gotoTiang(1));
  delay(1);
}
