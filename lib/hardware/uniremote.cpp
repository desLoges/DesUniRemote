#include "uniremote.h"


void init_guestrure_sensor(SparkFun_APDS9960 gs){
  pinMode(APDS9960_INT, INPUT);

  // Initialize interrupt service routine
  GUESTURE_INT_EN

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( gs.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( gs.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}

bool handleGesture(SparkFun_APDS9960 gs, IRsend ir) {
    if ( gs.isGestureAvailable() ) {
    switch ( gs.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        ir.sendNEC(0x20DFC23D, 32);
        delay(300);
        ir.sendNEC(0x20DF609F, 32);
        delay(300);
        ir.sendNEC(0x20DFDA25, 32);
        delay(300);
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        ir.sendNEC(0x20DF40BF, 32);
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        ir.sendNEC(0x20DFC03F, 32);
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
  return true;
}

void init_serial(void){
  Serial.begin(115200);
  Serial.println();
}

void fatal_error(void){
  BUILDIN_LED_ON
  delay(100);
  BUILDIN_LED_OFF
  delay(1000);
}
