#include <Wire.h>
#include "ESP8266WiFiMulti.h"
#include <SparkFun_APDS9960.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>
#include <RCSwitch.h>
#include "private.h"

//

// Pins on wemos D1 mini
#define I2C_PIN_SDA         D3
#define I2C_PIN_SCL         D1
#define APDS9960_INT        D6
#define IR_LED              D2
#define RF_SEND             D4
#define RF_RECEIVE          D5

#define WIFI_CONNECT_RETRY_LIMIT 20

#define LED_BUILTIN_ON      digitalWrite(BUILTIN_LED, HIGH);
#define LED_BUILTIN_OFF     digitalWrite(BUILTIN_LED, LOW);

#define GUESTURE_INT_EN     attachInterrupt(APDS9960_INT, int_guesture, FALLING);
#define GUESTURE_INT_DIS    detachInterrupt(APDS9960_INT);
