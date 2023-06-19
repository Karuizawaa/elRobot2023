#include <Ps3Controller.h>

#define POSM1 45
#define POSM2 135
#define POSM3 225
#define POSM4 315

#define RADIUSMTR 0.1 //meter
#define RADIUSBAN 0.243

float toRad(float degree) {
  return degree * M_PI / 180;
}

int player = 0;
int battery = 0;

void notify()
{
    //--- Digital cross/square/triangle/circle button events ---
//    if( Ps3.event.analog_changed.button.cross ){
//        Serial.println("X");
//    }
////    if( Ps3.event.button_up.cross )
////        Serial.println("Released the cross button");
//
//    if( Ps3.event.analog_changed.button.square ){
//        Serial.println("S");
//    }
////    if( Ps3.event.button_up.square )
////        Serial.println("Released the square button");
//
//    if( Ps3.event.analog_changed.button.triangle ){
//        Serial.println("T");
//    }
////    if( Ps3.event.button_up.triangle )
////        Serial.println("Released the triangle button");
//
//    if( Ps3.event.analog_changed.button.circle ){
//        Serial.println("C");
//    }
//    if( Ps3.event.button_up.circle )
//        Serial.println("Released the circle button");

    //--------------- Digital D-pad button events --------------
//    if( Ps3.event.button_down.up )
//        Serial.println("Started pressing the up button");
//    if( Ps3.event.button_up.up )
//        Serial.println("Released the up button");
//
//    if( Ps3.event.button_down.right )
//        Serial.println("Started pressing the right button");
//    if( Ps3.event.button_up.right )
//        Serial.println("Released the right button");
//
//    if( Ps3.event.button_down.down )
//        Serial.println("Started pressing the down button");
//    if( Ps3.event.button_up.down )
//        Serial.println("Released the down button");
//
//    if( Ps3.event.button_down.left )
//        Serial.println("Started pressing the left button");
//    if( Ps3.event.button_up.left )
//        Serial.println("Released the left button");
//
//    //------------- Digital shoulder button events -------------
//    if( Ps3.event.button_down.l1 )
//        Serial.println("Started pressing the left shoulder button");
//    if( Ps3.event.button_up.l1 )
//        Serial.println("Released the left shoulder button");
//
//    if( Ps3.event.button_down.r1 )
//        Serial.println("Started pressing the right shoulder button");
//    if( Ps3.event.button_up.r1 )
//        Serial.println("Released the right shoulder button");

    //-------------- Digital trigger button events -------------
//    if( Ps3.event.button_down.l2 )
//        Serial.println("Started pressing the left trigger button");
//    if( Ps3.event.button_up.l2 )
//        Serial.println("Released the left trigger button");
//
//    if( Ps3.event.button_down.r2 )
//        Serial.println("Started pressing the right trigger button");
//    if( Ps3.event.button_up.r2 )
//        Serial.println("Released the right trigger button");

    //--------------- Digital stick button events --------------
//    if( Ps3.event.button_down.l3 )
//        Serial.println("Started pressing the left stick button");
//    if( Ps3.event.button_up.l3 )
//        Serial.println("Released the left stick button");
//
//    if( Ps3.event.button_down.r3 )
//        Serial.println("Started pressing the right stick button");
//    if( Ps3.event.button_up.r3 )
//        Serial.println("Released the right stick button");
//
//    //---------- Digital select/start/ps button events ---------
//    if( Ps3.event.button_down.select )
//        Serial.println("Started pressing the select button");
//    if( Ps3.event.button_up.select )
//        Serial.println("Released the select button");
//
//    if( Ps3.event.button_down.start )
//        Serial.println("Started pressing the start button");
//    if( Ps3.event.button_up.start )
//        Serial.println("Released the start button");
//
//    if( Ps3.event.button_down.ps )
//        Serial.println("Started pressing the Playstation button");
//    if( Ps3.event.button_up.ps )
//        Serial.println("Released the Playstation button");


    //---------------- Analog stick value events ---------------
   if( abs(Ps3.event.analog_changed.stick.lx) || abs(Ps3.event.analog_changed.stick.ly) || abs(Ps3.event.analog_changed.button.l2) || abs(Ps3.event.analog_changed.button.r2)){
      int a = map(Ps3.data.analog.stick.lx, -128, 127, -128, 128);
      int b = map(Ps3.data.analog.stick.ly, -128, 127, 128, -128);
      int c = Ps3.data.analog.button.l2 - Ps3.data.analog.button.r2;
      if(a < 3 && a > -3) a = 0;
      if(b < 3 && b > -3) b = 0;
//      kinematic(a*7/128, b*7/128, c*8/128, 0);
      Serial2.print("X"); Serial2.println(a);
      Serial2.print("Y"); Serial2.println(b);
      Serial2.print("Z"); Serial2.println(c);
    }

//   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
//       Serial.print("Moved the right stick:");
//       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
//       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
//       Serial.println();
//   }

   //--------------- Analog D-pad button events ----------------
   if( abs(Ps3.event.button_down.up) ){
//       Serial.println("U");
      kinematic(0,-5,0,0);
      delay(3000);
      kinematic(0,0,0,0);
   }

   if( abs(Ps3.event.analog_changed.button.right) ){
//       Serial2.println("E");
   }

   if( abs(Ps3.event.analog_changed.button.down) ){
       Serial.println("D");
   }

   if( abs(Ps3.event.analog_changed.button.left) ){
       Serial.println("W");
   }

   //---------- Analog shoulder/trigger button events ----------
   if( abs(Ps3.event.analog_changed.button.l1)){
       Serial.println("L");
   }

   if( abs(Ps3.event.analog_changed.button.r1) ){
       Serial.println("R");
   }
//   if(abs(Ps3.event.analog_changed.button.l2) || abs(Ps3.event.analog_changed.button.r2)){
//       int c = Ps3.data.analog.button.l2 - Ps3.data.analog.button.r2;
//       Serial.print('Z'); Serial.println(c);
//       
//   }

//   if(abs(Ps3.event.analog_changed.button.l2) ){
//       int c = Ps3.data.analog.button.l2;
//       Serial.print('|'); Serial.println(c);
//       
//   }
//   if(abs(Ps3.event.analog_changed.button.r2) ){
//       int d = Ps3.data.analog.button.r2;
//       Serial.print('?'); Serial.println(d);
//       
//   }

   
   if( abs(Ps3.data.button.select) ){
       Serial.println("P");
   }

   
   if( abs(Ps3.data.button.start) ){
       Serial.println("M");
   }

   //---- Analog cross/square/triangle/circle button events ----
//   if( abs(Ps3.event.analog_changed.button.triangle)){
//       Serial.print("Pressing the triangle button: ");
//       Serial.println(Ps3.data.analog.button.triangle, DEC);
//   }

//   if( abs(Ps3.event.analog_changed.button.circle) ){
//       Serial.print("Pressing the circle button: ");
//       Serial.println(Ps3.data.analog.button.circle, DEC);
//   }

//   if( abs(Ps3.event.analog_changed.button.cross) ){
//       Serial.print("Pressing the cross button: ");
//       Serial.println(Ps3.data.analog.button.cross, DEC);
//   }
//
//   if( abs(Ps3.event.analog_changed.button.square) ){
//       Serial.print("Pressing the square button: ");
//       Serial.println(Ps3.data.analog.button.square, DEC);
//   }

   //---------------------- Battery events ---------------------
//    if( battery != Ps3.data.status.battery ){
//        battery = Ps3.data.status.battery;
//        Serial.print("The controller battery is ");
//        if( battery == ps3_status_battery_charging )      Serial.println("charging");
//        else if( battery == ps3_status_battery_full )     Serial.println("FULL");
//        else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
//        else if( battery == ps3_status_battery_low)       Serial.println("LOW");
//        else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
//        else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
//        else Serial.println("UNDEFINED");
//    }

}

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);
    Serial2.begin(9600);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("58:bf:25:8b:f4:2e");

}



void loop()
{
//  Serial2.println("w");
//  delay(1);
//  kinematic(0,3,0,0);
  
//  Serial2.print("!3.14");
//    if(!Ps3.isConnected())
//        return;

    //-------------------- Player LEDs -------------------
//    Serial.print("Setting LEDs to player "); Serial.println(player, DEC);
//    Ps3.setPlayer(player);
////
////    player += 1;
////    if(player > 10) player = 0;


    //------ Digital cross/square/triangle/circle buttons ------
//    if( Ps3.data.button.cross && Ps3.data.button.down )
//        Serial.println("Pressing both the down and cross buttons");
//    if( Ps3.data.button.square && Ps3.data.button.left )
//        Serial.println("Pressing both the square and left buttons");
//    if( Ps3.data.button.triangle && Ps3.data.button.up )
//        Serial.println("Pressing both the triangle and up buttons");
//    if( Ps3.data.button.circle && Ps3.data.button.right )
//        Serial.println("Pressing both the circle and right buttons");
//
//    if( Ps3.data.button.l1 && Ps3.data.button.r1 )
//        Serial.println("Pressing both the left and right bumper buttons");
//    if( Ps3.data.button.l2 && Ps3.data.button.r2 )
//        Serial.println("Pressing both the left and right trigger buttons");
//    if( Ps3.data.button.l3 && Ps3.data.button.r3 )
//        Serial.println("Pressing both the left and right stick buttons");
//    if( Ps3.data.button.select && Ps3.data.button.start )
//        Serial.println("Pressing both the select and start buttons");

    //delay(2000);
}
