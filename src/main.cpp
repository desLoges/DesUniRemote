/****************************************************************
****************************************************************/
#include "uniremote.h"

// Global Variables
volatile bool isr_guesture_flag = 0;
IRsend irsend(IR_LED);
SparkFun_APDS9960 guestsens = SparkFun_APDS9960();
RCSwitch mySwitch = RCSwitch();

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  BUILDIN_LED_ON

  // Initialize Serial port
  init_serial();
  Serial.println(F("Universal Remote start"));

  // Start I2C with pins defined above
  Wire.begin(I2C_PIN_SDA,I2C_PIN_SCL);
  // Start peripherals
  mySwitch.enableReceive(RF_RECEIVE);
  mySwitch.enableTransmit(RF_SEND);
  irsend.begin();

  init_guestrure_sensor(guestsens);
  BUILDIN_LED_OFF
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void loop() {
  if( isr_guesture_flag == 1 ) {
    GUESTURE_INT_DIS;
    handleGesture(guestsens, irsend);
    isr_guesture_flag = 0;
    GUESTURE_INT_EN;
  }

  BUILDIN_LED_ON
  delay(100);
  BUILDIN_LED_OFF
  delay(200);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void int_guesture() {
  isr_guesture_flag = 1;
}
