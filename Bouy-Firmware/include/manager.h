#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

#include "buoy.h"
#include "rasppi.h"
#include "sdcard.h"
#include "sensors/tdssensor.h"
#include "gpssensor.h"
#include "buoyble.h"

/**
 * The Manager class owns all objects except for the sensor which belong to Buoy.
 * It also handles all program logic.
 */
class Manager {
public:
  Manager();

  void createObjects();
  void execute();
  void setupTimers(); 
  void takeMeasurements();

  std::shared_ptr<Buoy> get_buoy() {return _buoy;}
  std::shared_ptr<RaspPi> get_rasppi() {return _rasppi;}
  std::shared_ptr<SDCard> get_sdcard() {return _sdcard;}
  std::shared_ptr<GPSSensor> get_gpssensor() {return _gpssensor;}
  std::shared_ptr<BuoyBLE> get_buoyble() {return _buoyble;}

  void startTransmission(){
    this->_startTransmission = true;
  }

private:
  std::shared_ptr<Buoy> _buoy;
  std::shared_ptr<RaspPi> _rasppi;
  std::shared_ptr<SDCard> _sdcard;
  std::shared_ptr<GPSSensor> _gpssensor;
  std::shared_ptr<BuoyBLE> _buoyble;

  volatile bool _startTransmission;
};

#endif
