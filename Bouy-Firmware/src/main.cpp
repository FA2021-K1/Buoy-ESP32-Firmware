#include <Arduino.h>

#include "ArduinoJson.h"

#include "buoyble.h"
#include "buoy.h"
#include "global_enums.h"
#include "gpssensor.h"
#include "hardwareLayout.h"
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
  Serial.println("Starting");
  manager.create_objects();
}

void loop() {
  manager.run();
  Location location(90.4, -30.7);
  std::string timestamp = "11:33:14, 2021.01.01";
  std::vector<Value> test_values;
  Value val1(111, 222, 33.3);
  test_values.push_back(val1);
  test_values.emplace_back(333, 5444, -1.4);
  SensorData sensordata(manager.get_buoy(), location, timestamp, test_values);
  Serial.println(sensordata.toJsonString().c_str());
  TransferDumpCommand dumpCommand = TransferDumpCommand(sensordata.toJsonString());
  Serial.println(dumpCommand.toJsonString().c_str());

  SyncCommand syncCommand = SyncCommand();
  Serial.println(syncCommand.toJsonString().c_str());

  RaspCommand* command = RaspCommand::fromJsonString("test12312312");

  Serial.println(command->toJsonString().c_str());

  while (1) {}
  // put your main code here, to run repeatedly:
}