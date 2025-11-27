#include "../include/SmartEdgeDevice.h"
#include <Arduino.h>

SmartEdgeDevice::SmartEdgeDevice()
    : dhtSensor(DHT_PIN, DHT_TYPE),
      acsSensor(ACS_PIN),
      led(LED_PIN),
      lastLogTime(0) {
}

void SmartEdgeDevice::setup() {
    Serial.println("Initializing Smart Edge (Motor)...");
    
    // Initialize components
    dhtSensor.begin();
    acsSensor.begin();
    
    // LED is initialized in its constructor (pinMode) but we can ensure state
    led.setState(false);

    Serial.println("Calibration Info:");
    acsSensor.printCalibration();
    Serial.println("System Ready.");
}

void SmartEdgeDevice::update() {
    unsigned long currentMillis = millis();

    // Read Sensors
    dhtSensor.read();
    
    uint32_t start = micros();
    int mA = acsSensor.readSampled();
    uint32_t stop = micros();

    // Logic: Check current threshold and trigger events
    if (abs(mA) > 1000) {
        on(Event(EVENT_HIGH_CURRENT));
    } else {
        on(Event(EVENT_NORMAL_CURRENT));
    }

    // Log every 5 seconds
    if (currentMillis - lastLogTime > 5000) {
        lastLogTime = currentMillis;

        Serial.print("Temp: ");
        Serial.print(dhtSensor.getTemperature());
        Serial.print(" C | Current (mA): ");
        Serial.print(mA);
        Serial.print(" | Form factor: ");
        Serial.print(acsSensor.getFormFactor());
        Serial.print(" | Time: ");
        Serial.println(stop - start);
    }
}

void SmartEdgeDevice::on(Event event) {
    if (event.id == EVENT_HIGH_CURRENT) {
        led.handle(Led::TURN_ON_COMMAND);
    } else if (event.id == EVENT_NORMAL_CURRENT) {
        led.handle(Led::TURN_OFF_COMMAND);
    }
}

void SmartEdgeDevice::handle(Command command) {
    // Pass commands to actuators if needed
    led.handle(command);
}

EnvironmentSensor& SmartEdgeDevice::getEnvironmentSensor() {
    return dhtSensor;
}

CurrentSensor& SmartEdgeDevice::getCurrentSensor() {
    return acsSensor;
}

Led& SmartEdgeDevice::getLed() {
    return led;
}

