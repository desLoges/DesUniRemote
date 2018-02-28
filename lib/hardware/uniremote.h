#include "hardware.h"


void init_serial(void);
void init_guestrure_sensor(SparkFun_APDS9960 gs);

bool set_wifiConnection(ESP8266WiFiMulti wifi_c);

bool handleGesture(SparkFun_APDS9960 gs, IRsend ir);
void int_guesture(void);

void fatal_error(void);
