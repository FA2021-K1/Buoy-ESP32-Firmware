#include <cstdlib>
#include <string>
#include <utility>
#include <cstdint>
#include <memory>
#include <SD.h>

#include "ArduinoJson.h"

#include "sdcard.h"
#include "sensordata.h"


SDCard::SDCard(uint16_t buoy_id) : _buoy_id(buoy_id) {
  Serial.println("Created SD Card");
}


void SDCard::init() {
  Serial.println("Now initializing SD Card");
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

  if (!SD.exists("/measurements")) {
    SD.mkdir("/measurements");
    Serial.println("Couldnt find measurements folder, created new one");
  }

  if (!SD.exists("/metadata")) {
    Serial.println("No metadata file found creating default");
    buoyStates_t default_states;
    default_states[_buoy_id] = std::pair<uint32_t, uint32_t>(0, 0);
    MetaData metadata(default_states);
    File new_file = SD.open("/metadata", FILE_WRITE);
    new_file.println(metadata.toJsonString().c_str());
    new_file.close();
  } else {
    Serial.println("Metadata file found");
  }
}


void SDCard::loadMetaData() {
  File metadata_file;
  buoyStates_t buoy_states;
  DynamicJsonDocument json_doc(96);

  // open file
  metadata_file = SD.open("/metadata", FILE_READ);
  Serial.println("Loading metadata file at /metadata");
  if (metadata_file) {
    // parse file
    Serial.println("Parsing json document");
    metadata_file.find("[");
    do {
      deserializeJson(json_doc, metadata_file);
      buoy_states[json_doc["buoyID"]] = std::pair<uint32_t, uint32_t>(json_doc["first"], 
                                                                      json_doc["last"]);
    } while (metadata_file.findUntil(",", "]"));
    // create MetaData object
    _meta_data = std::unique_ptr<const MetaData>(new MetaData(buoy_states));
    Serial.println("Parsing finished, printing MetaData:");
    _meta_data->print();
  } else {
    Serial.println("Error while loading metadata file");
    exit(1);
  }
}


void SDCard::writeSensorData(SensorData sensordata) {
  Serial.println("Writing sensordata");

  buoyStates_t new_buoy_states(_meta_data->_buoy_states);
  auto buoy_id = sensordata.get_buoy_id();
  auto current_mid = sensordata.get_measurement_id();
  auto last_mid = _meta_data->getLastMeasurementId(buoy_id);
  // if buoy_id is not already in metadata, create new entry
  if (_meta_data->_buoy_states.find(buoy_id) == _meta_data->_buoy_states.end()) {
    new_buoy_states[buoy_id] = std::pair<uint32_t, uint32_t>(current_mid, current_mid);
  }
  // check for consistency of metadata
  if (current_mid != last_mid) {
    Serial.println("Inconsistent write attempted! Aborting write");
    return;
  }
  // update metadata by incrementing last_id for current buoy
  new_buoy_states[buoy_id].second++;
  Serial.printf("Incremented last_id for buoy %d to %d\n", (uint) buoy_id,
                                             new_buoy_states[buoy_id].second);
  // update MetaData object                                             
  _meta_data = std::unique_ptr<const MetaData>(new MetaData(new_buoy_states));
  // also save updated metadata to sdcard
  std::string metadata_json = _meta_data->toJsonString();
  File metadata_file = SD.open("/metadata", FILE_WRITE);
  metadata_file.println(metadata_json.c_str());
  metadata_file.close();

  // save measurement data
  char filename[30];
  snprintf(filename, sizeof(filename), "/measurements/%u_%u", (uint) sensordata.get_buoy_id(),
                                                              (uint) sensordata.get_measurement_id());
  File json_file = SD.open(filename, FILE_WRITE);
  Serial.printf("Writing to file ");
  Serial.println(filename);
  if (json_file) {
    json_file.println(sensordata.toJsonString().c_str());
    Serial.println(sensordata.toJsonString().c_str());
    Serial.println("Writing done");
  } else {
    Serial.println("Writing Error");
  }
  json_file.close();

}


void SDCard::setMetaDataFirstIDs(buoyStates_t new_buoy_states) {
  ;
}


SensorData SDCard::readSensorData(uint16_t buoy_id, uint32_t measurement_id) {
  File sensordata_file;
  DynamicJsonDocument json_doc(248);

  // open file
  char filename[30];
  snprintf(filename, sizeof(filename), "/measurements/%u_%u", (uint) buoy_id, (uint) measurement_id);
  sensordata_file = SD.open(filename, FILE_READ);
  Serial.printf("Loading SensorData file at");
  Serial.println(filename);
  if (sensordata_file) {
    // parse header of file
    Serial.println("Now reading sensordata header");
    deserializeJson(json_doc, sensordata_file);
    SensorData sensordata(json_doc["buoyId"], json_doc["measurementId"],
                          Location_t(json_doc["latitude"], json_doc["longitude"]),
                          DateTime(json_doc["date"].as<std::string>()), std::vector<Value>());
    // parse values TODO SOMEHOW NOT WORKING
    Serial.println("Now parsing values");
    sensordata_file = SD.open(filename, FILE_READ);
    sensordata_file.find("\"measurements\":[");
    do {
      deserializeJson(json_doc, sensordata_file);
      sensordata.append_value(Value(json_doc["sensorType"], json_doc["sensorID"], json_doc["value"]));
    } while (sensordata_file.findUntil(",", "]"));

    // create SensorData object
    Serial.println("Parsing finished, printing SensorData:");
    Serial.println(sensordata.toJsonString().c_str());
    return sensordata;
  } else {
    Serial.println("Error while loading SensorData file");
    return SensorData();
  }
}
