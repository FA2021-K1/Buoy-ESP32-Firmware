#include <Arduino.h>

#include <libraries/ArduinoJson.h>

#include <hardwareclasses/rasppi.h>
#include <raspicom/raspcommands.h>
#include <hardwarelayout.h>


RaspPi::RaspPi() {
    Serial.println("Created RaspPi");
    pinMode(PI_RELAY_PIN, OUTPUT);
    digitalWrite(PI_RELAY_PIN, LOW);
}


void RaspPi::waitForReady() {
    char receivedChar;
    bool waiting = true;
    Serial.println("Waiting for r");
    while (waiting) {
        if (Serial.available() > 0) {
            receivedChar = Serial.read();
            if (receivedChar == 'r') {
                Serial.println("Received r");
                waiting = false;
            } else {
                Serial.printf("Received ");
                Serial.println(receivedChar);
            }
        }
    }
}


void RaspPi::writeData(std::string json_string) {
    Serial.printf("XXX");
    Serial.println(json_string.c_str());
}


void RaspPi::turnOn() {
    Serial.println("Turning on Raspberry");
    digitalWrite(PI_RELAY_PIN, HIGH);
}


void RaspPi::turnOff() {
    Serial.println("Turning off Raspberry");
    digitalWrite(PI_RELAY_PIN, LOW);
}
