
#include "raspberryPiInterface.h"
#include "hardwareLayout.h"
#include <Arduino.h>

void initRaspPi(struct RaspPi *pi){
    pi->online = false;
    pi->turningOn = false;
    pinMode(PI_RELAY_PIN,OUTPUT);
    digitalWrite(PI_RELAY_PIN,LOW);
}

void turnOnPi(struct RaspPi *pi){
    pi->online = false;
    digitalWrite(PI_RELAY_PIN,HIGH);
}

void turnOffPi(struct RaspPi *pi){
    pi->online = false;
    digitalWrite(PI_RELAY_PIN,LOW);
}