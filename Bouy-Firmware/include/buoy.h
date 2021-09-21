/***
 * Class to hold all information of the buoy
 */
#ifndef BUOY_H
#define BUOY_H

#include "sensor.h"
#include <vector>

class Buoy
{
protected:
  Buoy(unsigned int buoy_id);
  ~Buoy();
  static Buoy *_buoy;

public:
  Buoy(Buoy &other) = delete;
  void operator=(const Buoy &other) = delete;
  static Buoy *getInstance();

  void attachSensor(Sensor *sensor);

private:
  unsigned int _buoyID;
  std::vector<Sensor *> _sensors;
};

#endif BUOY_H