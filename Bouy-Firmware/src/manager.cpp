#include <memory>

#include "manager.h"
#include "buoy.h"
#include "rasppi.h"
#include "sensordata.h"
#include "value.h"
#include "sensors/analogsensor.h"

void Manager::create_objects() {
    _buoy = std::make_shared<Buoy>(1234);
    _tdssensor = std::make_shared<TDSSensor>(15);
    _rasppi = std::make_shared<RaspPi>();
    _sdcard = std::make_shared<SDCard>();
    _gpssensor = std::make_shared<GPSSensor>();
    
    _sdcard->init();
    _gpssensor->init();
}

void Manager::execute() {
    // todo turn on relay

    Location location = _gpssensor->getLocation();
    DateTime datetime = _gpssensor->getDateTime();
    std::vector<Value> values;
    values.emplace_back(2, 1, _tdssensor->get_ppm_value());
    SensorData sensordata(_buoy, location, datetime.to_iso(), values);

    // todo send to raspy
}