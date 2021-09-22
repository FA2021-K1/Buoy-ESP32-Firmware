#include <memory>

#include "buoy.h"
#include "rasppi.h"
#include "sensordata.h"
#include "raspicom/raspcommands.h"
#include "manager.h"

void Manager::create_objects()
{
    _buoy = std::make_shared<Buoy>(1234);
    _rasppi = std::make_shared<RaspPi>();
    _sdcard = std::make_shared<SDCard>();
    _sdcard->init();
}

void Manager::run()
{
    _rasppi->turnOn();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    Location location(90.4, -30.7);
    std::string timestamp = "11:33:14, 2021.01.01";
    std::vector<Value> test_values;
    Value val1(111, 222, 33.3);
    test_values.push_back(val1);
    test_values.emplace_back(333, 5444, -1.4);
    SensorData sensordata(_buoy, location, timestamp, test_values);
    Serial.println(sensordata.toJsonString().c_str());
    TransferDumpCommand dumpCommand = TransferDumpCommand(sensordata.toJsonString());
    Serial.println(dumpCommand.toJsonString().c_str());
    
    _rasppi->writeData(dumpCommand.toJsonString());
}