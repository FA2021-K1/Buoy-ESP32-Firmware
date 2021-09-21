#include <SDCardInterface.h>
#include <SD.h>
#include <SPI.h> 
 
void init_sd() {
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

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
      Serial.println("MMC");
  } else if (cardType == CARD_SD) {
      Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}