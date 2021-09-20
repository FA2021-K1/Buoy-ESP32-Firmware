/***
 * Interface for the raspberrypi
 * Provides functions and structs to wakeup the Raspberry Pi
 * and communicate sensor data
 */
#ifndef RASPBERRYPI_INTERFACE_H
#define RASPBERRYPI_INTERFACE_H

#include "stdbool.h"
#include "driver/uart.h"

struct RaspPi{
    bool online;
    bool turningOn;
    uint8_t rxbuf[256];
    uart_config_t *uart_config;
    QueueHandle_t uart_queue;
};

void initRaspPi(struct RaspPi *pi);
void deinitRaspPi(struct RaspPi *pi);
void turnOnRaspPi(struct RaspPi *pi);
void turnOffRaspPi(struct RaspPi *pi);

#endif