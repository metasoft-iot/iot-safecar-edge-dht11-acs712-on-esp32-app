#ifndef SMART_EDGE_DEVICE_H
#define SMART_EDGE_DEVICE_H

#include "Device.h"
#include "EnvironmentSensor.h"
#include "CurrentSensor.h"
#include "Led.h"
#include "EdgeServiceClient.h"  // HTTP client for Edge Service

class SmartEdgeDevice : public Device {
private:
    EnvironmentSensor dhtSensor;
    CurrentSensor acsSensor;
    Led led;
    EdgeServiceClient edgeClient;  // Edge service client
    unsigned long lastLogTime;
    unsigned long lastSend;        // Timestamp for telemetry sending

public:
    // Constants for pins
    static const int DHT_PIN = 4;
    static const int DHT_TYPE = DHT22;
    static const int ACS_PIN = 35;
    static const int LED_PIN = 2;

    // Event IDs
    static const int EVENT_HIGH_CURRENT = 10;
    static const int EVENT_NORMAL_CURRENT = 11;

    // Telemetry Sending Interval
    static const unsigned long SEND_INTERVAL = 10000;  // Send every 10 seconds

    SmartEdgeDevice();

    void setup();
    void update(); // Main loop logic

    // Device interface implementation
    void on(Event event) override;
    void handle(Command command) override;

    // Accessors if needed
    EnvironmentSensor& getEnvironmentSensor();
    CurrentSensor& getCurrentSensor();
    Led& getLed();
};

#endif // SMART_EDGE_DEVICE_H

