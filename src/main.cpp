/****************************************************************
****************************************************************/
#include "uniremote.h"

// Global Variables
volatile bool isr_guesture_flag = 0;

// Objects
ESP8266WiFiMulti WiFiMulti;
IRsend irsend(IR_LED);
SparkFun_APDS9960 guestsens = SparkFun_APDS9960();
RCSwitch mySwitch = RCSwitch();

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  LED_BUILTIN_ON

  // Initialize Serial port
  init_serial();
  Serial.println(F("Universal Remote start"));

  if( !set_wifiConnection(WiFiMulti) ){
   ESP.restart();
  }

  // Start I2C with pins defined above
  Wire.begin(I2C_PIN_SDA,I2C_PIN_SCL);

  // Start peripherals
  mySwitch.enableReceive(RF_RECEIVE);
  mySwitch.enableTransmit(RF_SEND);
  irsend.begin();
  init_guestrure_sensor(guestsens);


  String url = "http://";
  url += WIFI_LED_STRIP_IP;
  url += "/api/color?apikey=82C05D44978333AD&value=255,0,0"; ///"/trigger/door_status/with/key/";  //&value=#0055ff

  send_http_request(url);
  LED_BUILTIN_OFF
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

  LED_BUILTIN_ON
  delay(100);
  LED_BUILTIN_OFF
  delay(200);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void int_guesture() {
  isr_guesture_flag = 1;
}
