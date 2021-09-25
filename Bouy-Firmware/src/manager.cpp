#include <memory>

#include "buoy.h"
#include "manager.h"
#include "rasppi.h"
#include "sensordata.h"
#include "value.h"
#include "sensors/analogsensor.h"
#include "raspicom/raspcommands.h"
#include "buoyble.h"
#include "datetime.h"

void Manager::create_objects()
{
    _buoy = std::make_shared<Buoy>(1234);
    _rasppi = std::make_shared<RaspPi>();
    _sdcard = std::make_shared<SDCard>();
    _gpssensor = std::make_shared<GPSSensor>();
    _buoyble = std::make_shared<BuoyBLE>();

    // attach sensors
    _buoy->attachSensor(std::make_shared<TDSSensor>(123, 45));
    
    _sdcard->init();
    _gpssensor->init();
    _buoyble->init();
}

void Manager::execute() {
    // wait for ping from BLE module
    while (!_buoyble->getValue_bool()) {
        delay(1000);
    }

    // poll time and location from GPS module
    Location location = _gpssensor->get_location();
    DateTime datetime = _gpssensor->get_datetime();

    // // mock gps data
    // Location location(123, -1.2);
    // DateTime datetime(2013, 11, 11, 11, 11, 11, 99);

    // sample all sensors (currently one) and create SensorData instance
    auto all_values = _buoy->sampleAllSensors();
    SensorData sensordata(_buoy, location, datetime, all_values);

    // print to json string to Serial
    Serial.println(sensordata.toJsonString().c_str());

    _rasppi->turnOn();

    vTaskDelay(10000 / portTICK_PERIOD_MS);
    TransferDumpCommand dumpCommand = TransferDumpCommand(sensordata.toJsonString());    
    _rasppi->writeData(dumpCommand.toJsonString());
    //_rasppi->turnOff()
}