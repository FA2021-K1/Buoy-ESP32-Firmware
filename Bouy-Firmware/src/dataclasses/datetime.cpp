#include <cstdio>

#include "dataclasses/datetime.h"

DateTime::DateTime(uint16_t year_, uint8_t month_, uint8_t day_,
                    uint8_t hour_, uint8_t minute_, uint8_t second_,
                    uint8_t centisecond_) : year(year_), month(month_),
                    day(day_), hour(hour_), minute(minute_), second(second_),
                    centisecond(centisecond_) {}

DateTime::DateTime() : year(0), month(0), day(0), hour(0), minute(0), second(0), centisecond(0) {}

DateTime::DateTime(std::string iso) {
  year   = std::stoi(iso.substr(0,  4));
  month  = std::stoi(iso.substr(5,  2));
  day    = std::stoi(iso.substr(8,  2));
  hour   = std::stoi(iso.substr(11, 2));
  minute = std::stoi(iso.substr(14, 2));
  second = std::stoi(iso.substr(17, 2));
}

std::string DateTime::to_iso() {
  unsigned int string_length = 21;
  char string_buffer[string_length];
  // Y Y Y Y - M M - D D T  H  H  :  M  M  :  S  S  Z
  // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
  snprintf(string_buffer, string_length, "%04u-%02u-%02uT%02u:%02u:%02uZ",
          static_cast<uint>(year), static_cast<uint>(month), static_cast<uint>(day),
          static_cast<uint>(hour), static_cast<uint>(minute), static_cast<uint>(second));
  return string_buffer;
}

// std::string DateTime::to_filename() {
//   unsigned int string_length = 20;
//   char string_buffer[string_length];
//   snprintf(string_buffer, string_length, "%04u-%02u-%02u_%02u-%02u-%02u",
//           static_cast<uint>(year), static_cast<uint>(month), static_cast<uint>(day),
//           static_cast<uint>(hour), static_cast<uint>(minute), static_cast<uint>(second));
//   return string_buffer;
// }