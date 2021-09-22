#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

#include "buoy.h"
#include "rasppi.h"
#include "sdcard.h"
#include "sensors/tdssensor.h"
#include "gpssensor.h"


class Manager {
public:
  Manager() {}
  void create_objects();
  void execute();
  std::shared_ptr<Buoy> get_buoy() {return _buoy;}
  std::shared_ptr<RaspPi> get_rasppi() {return _rasppi;}
  std::shared_ptr<SDCard> get_sdcard() {return _sdcard;}
  std::shared_ptr<GPSSensor> get_gpssensor() {return _gpssensor;}
private:
  std::shared_ptr<Buoy> _buoy;
  std::shared_ptr<RaspPi> _rasppi;
  std::shared_ptr<SDCard> _sdcard;
  std::shared_ptr<GPSSensor> _gpssensor;
  std::shared_ptr<TDSSensor> _tdssensor;
};

#endif
