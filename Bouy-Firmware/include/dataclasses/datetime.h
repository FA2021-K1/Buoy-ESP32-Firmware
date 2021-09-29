#ifndef DATETIME_H
#define DATETIME_H

#include <Arduino.h>

#include <cstdint>

/**
 * Dataclass for timestamps. 
 */
class DateTime {
    public:
        /**
         * Create from uints.
         */
        DateTime(uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
        /**
         * Create from iso-string.
         */
        DateTime(std::string);
        /**
         * Create all zero datetime
         */
        DateTime();

        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        uint8_t centisecond;

        /**
         * Returns ISO-8601 formatted timestamp string (no centiseconds and timezone)
         */
        std::string to_iso();
};

#endif