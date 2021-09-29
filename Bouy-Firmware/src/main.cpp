#include <Arduino.h>
#include "manager.h"

#include "hardwarelayout.h"

Manager manager;


void setup() {
  Serial.begin(115200);
  // manager.createObjects();
  // manager.setupTimers();
}


void loop() {
  Serial.printf("TDS ");
  Serial.println(analogRead(TDS_PIN));
  Serial.printf("PH ");
  Serial.println((double) analogRead(PH_PIN) / 4096 * 3300);
  // manager.execute();
  delay(2000);
}