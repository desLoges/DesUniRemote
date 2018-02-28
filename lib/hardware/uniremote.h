#include "hardware.h"


void init_serial(void);
void init_guestrure_sensor(SparkFun_APDS9960 gs);

bool handleGesture(SparkFun_APDS9960 gs, IRsend ir);
void int_guesture(void);

void fatal_error(void);
