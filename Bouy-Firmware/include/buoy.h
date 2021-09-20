/***
 * Class to hold all information of the buoy
 */
#ifndef BUOY_H
#define BUOY_H

#include <vector>

class Buoy {
protected:
  Buoy(unsigned int buoy_id);
  ~Buoy();
  static Buoy* _buoy;

public:
  Buoy(Buoy &other) = delete;
  void operator=(const Buoy &other) = delete;
  static Buoy* getInstance();

  void attachSensor(unsigned int sensor_id);
  std::vector<unsigned int> getSensorIDs();

private:
  unsigned int _buoyID;
  std::vector<unsigned int> _sensorIDs;
};

#endif BUOY_H