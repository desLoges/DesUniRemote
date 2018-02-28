#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>


// Pins on wemos D1 mini
#define I2C_PIN_SDA         D3
#define I2C_PIN_SCL         D1
#define APDS9960_INT    D6
#define IR_LED          D2
#define RF_SEND         0

#define BUILDIN_LED_ON      digitalWrite(BUILTIN_LED, HIGH);
#define BUILDIN_LED_OFF     digitalWrite(BUILTIN_LED, LOW);

#define GUESTURE_INT_EN     attachInterrupt(APDS9960_INT, int_guesture, FALLING);
#define GUESTURE_INT_DIS    detachInterrupt(APDS9960_INT);
