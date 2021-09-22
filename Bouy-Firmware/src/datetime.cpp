#include <cstdio>

#include "datetime.h"

DateTime::DateTime(uint16_t year_, uint8_t month_, uint8_t day_,
                    uint8_t hour_, uint8_t minute_, uint8_t second_,
                    uint8_t centisecond_) : year(year_), month(month_),
                    day(day_), hour(hour_), minute(minute_), second(second_),
                    centisecond(centisecond_) {}

std::string DateTime::to_iso() {
  unsigned int string_length = 21;
  char string_buffer[string_length];
  snprintf(string_buffer, string_length, "%04u-%02u-%02uT%02u:%02u:%02uZ",
          static_cast<uint>(year), static_cast<uint>(month), static_cast<uint>(day),
          static_cast<uint>(hour), static_cast<uint>(minute), static_cast<uint>(second));
  return string_buffer;
}

std::string DateTime::to_filename() {
  unsigned int string_length = 20;
  char string_buffer[string_length];
  snprintf(string_buffer, string_length, "%04u-%02u-%02u_%02u-%02u-%02u",
          static_cast<uint>(year), static_cast<uint>(month), static_cast<uint>(day),
          static_cast<uint>(hour), static_cast<uint>(minute), static_cast<uint>(second));
  return string_buffer;
}