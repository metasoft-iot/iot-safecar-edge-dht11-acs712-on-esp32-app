#include "../include/CurrentSensor.h"
#include <Arduino.h>

CurrentSensor::CurrentSensor(int pin, EventHandler* eventHandler)
    : Sensor(pin, eventHandler), acs(pin, 3.3, 4095, 185), currentDC(0.0) {
}

void CurrentSensor::begin() {
    acs.autoMidPoint();
}

void CurrentSensor::read() {
    currentDC = acs.mA_DC();
}

int CurrentSensor::readSampled() {
    return acs.mA_AC_sampling();
}

float CurrentSensor::getCurrentDC() const {
    return currentDC;
}

int CurrentSensor::getFormFactor() {
    return acs.getFormFactor();
}

void CurrentSensor::printCalibration() {
    Serial.print("MidPoint: ");
    Serial.print(acs.getMidPoint());
    Serial.print(". Noise mV: ");
    Serial.println(acs.getNoisemV());
}

