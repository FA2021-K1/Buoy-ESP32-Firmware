#ifndef LORA_MODULE_H
#define LORA_MODULE_H

#include <Arduino.h>

#include "hardwarelayout.h"

class LoraModule {
public:
  LoraModule() {
    // to pull chip select of lora low!
    pinMode(LORA_CS_PIN, OUTPUT);
    digitalWrite(LORA_CS_PIN, HIGH);
  }
};

#endif