#include <Arduino.h>

#include "ArduinoJson.h"

#include "buoyble.h"
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

BuoyBLE ble;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("LEN= ");
  ble.init();
}

void loop() {
  Serial.println("hi");
  delay(1000);
  Serial.println(ble.getValue().c_str());
  Serial.println(ble.getValue_bool());
  // put your main code here, to run repeatedly:
}