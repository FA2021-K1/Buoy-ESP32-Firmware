#include <Arduino.h>
#include "manager.h"


Manager manager;


void setup() {
  Serial.begin(115200);
  manager.createObjects();
  manager.setupTimers();
}


void loop() {
  manager.execute();
  delay(1000);
}