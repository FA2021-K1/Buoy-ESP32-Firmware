#include <memory>
#include <cstdint>
#include <vector>

#include "ArduinoJson.h"

#include "value.h"
#include "buoy.h"
#include "sensordata.h"
#include "global_enums.h"
#include "datetime.h"

SensorData::SensorData(uint16_t buoy_id, uint32_t measurement_id, Location_t location,
                       DateTime timestamp, std::vector<Value> values) :
                       _buoy_id(buoy_id), _measurement_id(measurement_id), 
                       _location(location), _timestamp(timestamp), _values(values), _found(true) {}

SensorData::SensorData() : _found(false) {}


std::string SensorData::toJsonString() {
  // size determined using https://arduinojson.org/v6/assistant/
  DynamicJsonDocument json_doc(128 + 96 * _values.size()); 
  json_doc["buoyId"] = _buoy_id;
  json_doc["measurementId"] = _measurement_id;
  json_doc["date"] = _timestamp.to_iso();
  json_doc["latitude"] = _location.first;
  json_doc["longitude"] = _location.second;
  
  for (unsigned int index=0; index < _values.size(); index++) {
    json_doc["measurements"][index]["sensorID"] = _values[index].sensor_id;
    json_doc["measurements"][index]["sensorType"] = _values[index].type_id;
    json_doc["measurements"][index]["value"] = _values[index].data;
  }

  std::string json_string;
  serializeJson(json_doc, json_string);
  return json_string;
}