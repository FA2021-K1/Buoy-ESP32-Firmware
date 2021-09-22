#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

#include "buoy.h"
#include "rasppi.h"
#include "sdcard.h"


class Manager {
public:
  Manager() {}
  void create_objects();
  std::shared_ptr<Buoy> get_buoy() {return _buoy;}
  std::shared_ptr<RaspPi> get_rasppi() {return _rasppi;}
  std::shared_ptr<SDCard> get_sdcard() {return _sdcard;}
  void run();
private:
  std::shared_ptr<Buoy> _buoy;
  std::shared_ptr<RaspPi> _rasppi;
  std::shared_ptr<SDCard> _sdcard;
};

#endif
