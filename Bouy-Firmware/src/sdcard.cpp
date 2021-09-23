#include <SD.h>

#include "ArduinoJson.h"

#include <sdcard.h>


void SDCard::init() {
  if (!SD.begin()) {
      Serial.println("Card Mount Failed");
      return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
      Serial.println("No SD card attached");
      return;
  }
  Serial.println("SD card initializied successfully");

  Serial.print("SD card Type: ");
  if (cardType == CARD_MMC) {
      Serial.println("MMC");
  } else if (cardType == CARD_SD) {
      Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }

  _capacity = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD card size %lu MB\n", static_cast<unsigned long>(_capacity));
}

void SDCard::writeData(std::string json_string) {
// TODO UPDATE

  // File json_file = SD.open(filename.c_str(), FILE_WRITE);
  // Serial.printf("Writing to file ");
  // Serial.println(filename.c_str());
  // if (json_file) {
  //   json_file.println(json_string.c_str());
  //   json_file.close();
  //   Serial.println("Writing done");
  // } else {
  //   Serial.println("Error");
  // }
}

std::string SDCard::readData() {
  // TODO IMPLEMENT
}
