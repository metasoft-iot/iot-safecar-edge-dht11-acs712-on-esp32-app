#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include "Sensor.h"
#include <ACS712.h>

class CurrentSensor : public Sensor {
private:
    ACS712 acs;
    float currentDC;

public:
    CurrentSensor(int pin, EventHandler* eventHandler = nullptr);
    void begin();
    void read(); // Reads DC or default read
    int readSampled(); // Wrapper for mA_AC_sampling
    float getCurrentDC() const;
    int getFormFactor();
    void printCalibration();
};

#endif // CURRENT_SENSOR_H

