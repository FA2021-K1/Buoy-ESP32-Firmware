#ifndef DATETIME_H
#define DATETIME_H

#include <Arduino.h>

#include <cstdint>


class DateTime {
    public:
        DateTime();
        DateTime(uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        uint8_t centisecond;

        std::string to_iso();
        std::string to_filename();
};

#endif