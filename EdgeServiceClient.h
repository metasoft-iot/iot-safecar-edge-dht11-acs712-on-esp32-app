#ifndef EDGE_SERVICE_CLIENT_H
#define EDGE_SERVICE_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/**
 * @brief Client for sending telemetry data to SafeCar Edge Service (MOTOR)
 * 
 * Handles WiFi connection and HTTP POST requests to the Edge Service.
 * Supports both Wokwi simulation and real hardware deployment.
 */
class EdgeServiceClient {
private:
    // WiFi Configuration
    // WOKWI (Active - for simulation testing)
    const char* wifiSsid = "Wokwi-GUEST";
    const char* wifiPassword = "";
    
    // REAL HARDWARE (Commented - uncomment for real ESP32)
    // const char* wifiSsid = "YOUR_WIFI_SSID";
    // const char* wifiPassword = "YOUR_WIFI_PASSWORD";

    // Edge Service Configuration
    // WOKWI (Active - replace with your computer's local IP)
    // To find your IP: 
    //   - Windows: ipconfig
    //   - Mac/Linux: ifconfig or ip addr
    String edgeServiceUrl = "http://192.168.1.100:5000/api/v1/telemetry/data-records";
    
    // REAL HARDWARE (Commented - use this for real ESP32 on same network)
    // String edgeServiceUrl = "http://192.168.1.100:5000/api/v1/telemetry/data-records";

    // Device Authentication (same for both Wokwi and real)
    const char* deviceId = "safecar-001";
    const char* apiKey = "test-api-key-12345";

    HTTPClient httpClient;

public:
    EdgeServiceClient();
    
    /**
     * @brief Connect to WiFi network
     * @return true if connected successfully
     */
    bool connectWiFi();
    
    /**
     * @brief Send telemetry data from MOTOR sensors to Edge Service
     * @param temperature Engine temperature in Celsius (DHT11)
     * @param currentAmperes Current in Amperes (ACS712)
     * @return true if data sent successfully
     * 
     * Note: Humidity not included because EnvironmentSensor only measures temperature
     */
    bool sendTelemetry(float temperature, float currentAmperes);
    
    /**
     * @brief Check if WiFi is connected
     * @return true if connected
     */
    bool isConnected();
};

#endif // EDGE_SERVICE_CLIENT_H
