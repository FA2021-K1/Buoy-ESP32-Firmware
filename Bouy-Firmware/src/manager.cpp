#include <memory>

#include "buoy.h"
#include "manager.h"
#include "rasppi.h"
#include "sensordata.h"
#include "value.h"
#include "sensors/tdssensor.h"
#include "raspicom/raspcommands.h"
#include "buoyble.h"
#include "datetime.h"
 
hw_timer_t * measurement_timer = NULL;
portMUX_TYPE measurement_timer_mux = portMUX_INITIALIZER_UNLOCKED;
Manager* manager_pointer = nullptr;

void IRAM_ATTR measurementCallback() {
    portENTER_CRITICAL_ISR(&measurement_timer_mux);
    Serial.println("Measurement Interrupt called!");
    manager_pointer->takeMeasurements();
    portEXIT_CRITICAL_ISR(&measurement_timer_mux);
}


Manager::Manager() {
    _startTransmission = false;
    manager_pointer = this;
}


void Manager::setupTimers() {
    measurement_timer = timerBegin(0, 80000, true);
    timerAttachInterrupt(measurement_timer, &measurementCallback, true);
    timerAlarmWrite(measurement_timer, 10*1000, true);
    timerAlarmEnable(measurement_timer);
 
}


void Manager::takeMeasurements() {

    // // poll time and location from GPS module
    // Location_t location = _gpssensor->get_location();
    // DateTime datetime = _gpssensor->get_datetime();

    // mock gps data
    Location_t location(123, -1.2);
    DateTime datetime(2013, 11, 11, 11, 11, 11, 99);

    // sample all sensors and create SensorData instance
    auto all_values = _buoy->sampleAllSensors();
    auto buoy_id = _buoy->get_buoy_id();
    auto last_id = _sdcard->get_buoy_states().at(buoy_id).second;
    SensorData sensordata(buoy_id, last_id, location, datetime, all_values);

    // print to json string to Serial and save to sdcard
    Serial.println("obtained measurement: ");
    Serial.println(sensordata.toJsonString().c_str());
    _sdcard->writeSensorData(sensordata);
}


void Manager::createObjects()
{
    _buoy = std::make_shared<Buoy>(1234);
    // _rasppi = std::make_shared<RaspPi>();
    _sdcard = std::make_shared<SDCard>(_buoy->get_buoy_id());
    // _gpssensor = std::make_shared<GPSSensor>();
    // _buoyble = std::make_shared<BuoyBLE>();

    // attach sensors
    _buoy->attachSensor(std::make_shared<TDSSensor>(7));
    _buoy->attachSensor(std::make_shared<TDSSensor>(18));
    
    _sdcard->init();
    // _gpssensor->init();
    // _buoyble->init();

    _sdcard->loadMetaData();

}

void Manager::execute() {
    while (1);
    // // wait for ping from BLE module
    // while (!_buoyble->getValue_bool()) {
    //     delay(1000);
    // }

    // SensorData test_read = _sdcard->readSensorData(_buoy->get_buoy_id(), );
    // if (test_read) {Serial.println("FOUND FILE");}
    // else {Serial.println("FILE NOT FOUND");}

    // _rasppi->turnOn();
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    // TransferDumpCommand dumpCommand = TransferDumpCommand(sensordata.toJsonString());    
    // _rasppi->writeData(dumpCommand.toJsonString());

    // // wait for ping from BLE module
    // while (_buoyble->getValue_bool()) {
    //     delay(1000);
    // }
}