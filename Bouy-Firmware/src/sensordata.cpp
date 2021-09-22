#include <memory>

#include "ArduinoJson.h"

#include "value.h"
#include "buoy.h"
#include "sensordata.h"

typedef std::pair<double, double> Location;

SensorData::SensorData(std::shared_ptr<Buoy> buoy, Location location,
                       std::string timestamp, std::vector<Value> values) :
                       _buoy(buoy), _location(location), _timestamp(timestamp), _values(values) {}


std::string SensorData::toJsonString() {
  DynamicJsonDocument json_doc(1000);
  json_doc["buoyId"] = _buoy->get_buoy_id();
  json_doc["location"]["latitude"] = _location.first;
  json_doc["location"]["longitude"] = _location.second;
  
  for (unsigned int index=0; index < _values.size(); index++) {
    json_doc["measurements"][index]["sensorID"] = _values[index].sensor_id;
    json_doc["measurements"][index]["sensorType"] = _values[index].type_id;
    json_doc["measurements"][index]["measurement"] = _values[index].data;
  }
  std::string json_string;
  serializeJson(json_doc, json_string);
  return json_string;
}
