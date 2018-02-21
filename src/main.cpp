/****************************************************************
GestureTest.ino
APDS-9960 RGB and Gesture Sensor
Shawn Hymel @ SparkFun Electronics
May 30, 2014
https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor
Tests the gesture sensing abilities of the APDS-9960. Configures
APDS-9960 over I2C and waits for gesture events. Calculates the
direction of the swipe (up, down, left, right) and displays it
on a serial console.
To perform a NEAR gesture, hold your hand
far above the sensor and move it close to the sensor (within 2
inches). Hold your hand there for at least 1 second and move it
away.
To perform a FAR gesture, hold your hand within 2 inches of the
sensor for at least 1 second and then move it above (out of
range) of the sensor.
Hardware Connections:
IMPORTANT: The APDS-9960 can only accept 3.3V!

Wemos Pin  APDS-9960 Board  Function

 3.3V         VCC              Power
 GND          GND              Ground
 D3           SDA              I2C Data
 D1           SCL              I2C Clock
 D6           INT              Interrupt
 D7           -                LED
Resources:
Include Wire.h and SparkFun_APDS-9960.h
Development environment specifics:
Written in Arduino 1.0.5
Tested with SparkFun Arduino Pro Mini 3.3V
This code is beerware; if you see me (or any other SparkFun
employee) at the local, and you've found our code helpful, please
buy us a round!
Distributed as-is; no warranty is given.
Modified for ESP8266 by Jon Ulmer Nov 2016
****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>

// Pins on wemos D1 mini
#define APDS9960_INT    D6  //AKA GPIO12 -- Interupt pin
#define APDS9960_SDA    D3  //AKA GPIO0
#define APDS9960_SCL    D1  //AKA GPIO5
IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)
uint16_t RECV_PIN = 14;


void handleGesture();
void interruptRoutine();


// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
volatile bool isr_flag = 0;
// An IR detector/demodulator is connected to GPIO pin 14, D5 on a NodeMCU

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {

  //Start I2C with pins defined above
  Wire.begin(APDS9960_SDA,APDS9960_SCL);

  irrecv.enableIRIn();  // Start the receiver
  irsend.begin();

  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  pinMode(BUILTIN_LED, OUTPUT);

  // Initialize Serial port
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  attachInterrupt(APDS9960_INT, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}

void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(APDS9960_INT);
    Serial.println(F("check"));
    handleGesture();
    isr_flag = 0;
    attachInterrupt(APDS9960_INT, interruptRoutine, FALLING);
  }

  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }

  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(200);
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        irsend.sendNEC(0x20DFC23D, 32);
        delay(300);
        irsend.sendNEC(0x20DF609F, 32);
        delay(300);
        irsend.sendNEC(0x20DFDA25, 32);
        delay(300);
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        irsend.sendNEC(0x20DF40BF, 32);
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        irsend.sendNEC(0x20DFC03F, 32);
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
}
