/***
 * Definition of the hardware layout.
 * Which sensor/module is connected to which pin.
 */
#include "driver/uart.h"

// RELAY
#define PI_RELAY_PIN 13 // connect to IN pin on Relay

// GPS
#define GPS_RX_PIN 12 // connect to RX pin on GPS module
#define GPS_TX_PIN 14 // connect to TX pin on GPS module

// RASPPI UART
#define PI_UART UART_NUM_2
#define U2RXD 26
#define U2TXD 27