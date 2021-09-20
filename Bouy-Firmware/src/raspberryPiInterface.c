
#include "raspberryPiInterface.h"
#include "hardwareLayout.h"
#include "Arduino.h"

void initRaspPi(struct RaspPi *pi){
    pi->online = false;
    pi->requestedTurnOff = false;
    pinMode(PI_RELAY_PIN,OUTPUT);
    digitalWrite(PI_RELAY_PIN,LOW);
}