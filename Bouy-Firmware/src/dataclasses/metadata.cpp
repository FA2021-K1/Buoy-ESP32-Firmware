#include "libraries/ArduinoJson.h"

#include "dataclasses/metadata.h"

std::string MetaData::toJsonString() const {
  // size determined using https://arduinojson.org/v6/assistant/
  DynamicJsonDocument json_doc(96 * _buoy_states.size());
  JsonArray json_array = json_doc.to<JsonArray>();
  
  for (auto const& entry : _buoy_states) {
    auto buoy_id = entry.first;
    auto first_last = entry.second;
    JsonObject nested = json_array.createNestedObject();
    nested["buoyID"] = buoy_id;
    nested["first"] = first_last.first;
    nested["last"] = first_last.second;
  }

  std::string json_string;
  serializeJson(json_doc, json_string);
  return json_string;
}

void MetaData::print() const {
  for (auto const& entry : _buoy_states) {
    auto buoy_id = entry.first;
    auto first_last = entry.second;
    Serial.printf("BuoyID: %u ", (unsigned int) buoy_id);
    Serial.printf("from: %u ", (unsigned int) first_last.first);
    Serial.printf("to: %u \n", (unsigned int) first_last.second);
  }
}

uint32_t MetaData::getLastMeasurementId(uint16_t buoy_id) const {
  return _buoy_states.at(buoy_id).second;
}
