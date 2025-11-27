#include "EnvironmentSensor.h"

EnvironmentSensor::EnvironmentSensor(int pin, uint8_t type, EventHandler* eventHandler)
    : Sensor(pin, eventHandler), dht(pin, type), temperature(0.0) {
}

void EnvironmentSensor::begin() {
    dht.begin();
}

void EnvironmentSensor::read() {
    float temp = dht.readTemperature();
    if (!isnan(temp)) {
        temperature = temp;
    }
}

float EnvironmentSensor::getTemperature() const {
    return temperature;
}

