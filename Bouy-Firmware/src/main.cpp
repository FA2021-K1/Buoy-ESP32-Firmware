#include <Arduino.h>
#include <cstdio>

#include "ArduinoJson.h"

#include "buoyble.h"
#include "buoy.h"
#include "datetime.h"
#include "global_enums.h"
#include "gpssensor.h"
#include "hardwarelayout.h"
#include "manager.h"
#include "rasppi.h"
#include "sdcard.h"
#include "sensor.h"
#include "sensors/analogsensor.h"
#include "sensordata.h"
#include "transferdata.h"
#include "value.h"
#include <raspicom/raspcommands.h>


Manager manager;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  manager.create_objects();
}

void loop() {
  manager.execute()
  while (1) {}
}