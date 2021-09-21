#include <Arduino.h>

#include "bluetooth.h"
#include "buoy.h"
#include "global_enums.h"
#include "gpssensor.h"
#include "hardwareLayout.h"
#include "rasppi.h"
#include "sdcard.h"
#include "sensor.h"
#include "sensors/analogsensor.h"
#include "sensordata.h"
#include "transferdata.h"
#include "value.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("LEN= ");
}

void loop() {
  Serial.println("hi");
  delay(1000);
  // put your main code here, to run repeatedly:
}