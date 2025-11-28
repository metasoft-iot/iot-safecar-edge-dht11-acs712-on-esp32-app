#include "EdgeServiceClient.h"

EdgeServiceClient::EdgeServiceClient() {
    // Constructor - nothing to initialize
}

bool EdgeServiceClient::connectWiFi() {
    Serial.println("Connecting to WiFi...");
    Serial.print("SSID: ");
    Serial.println(wifiSsid);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSsid, wifiPassword);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✓ WiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        Serial.print("MAC Address: ");
        Serial.println(WiFi.macAddress());
        return true;
    } else {
        Serial.println("\n✗ WiFi Connection Failed!");
        return false;
    }
}

bool EdgeServiceClient::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

bool EdgeServiceClient::sendTelemetry(float temperature, float currentAmperes) {
    if (!isConnected()) {
        Serial.println("✗ WiFi not connected. Cannot send telemetry.");
        return false;
    }

    // Create JSON payload (NO humidity - EnvironmentSensor doesn't measure it)
    JsonDocument doc;
    doc["sensor_location"] = "MOTOR";
    doc["engine_temperature_celsius"] = temperature;
    doc["current_amperes"] = currentAmperes;
    
    // Timestamp (ISO 8601 format approximation)
    // Note: ESP32 doesn't have RTC, so we can't get real time without NTP
    // Edge service will use server time if timestamp is missing
    // For now, we'll omit timestamp and let server handle it
    
    // Serialize JSON to string
    String jsonPayload;
    serializeJson(doc, jsonPayload);
    
    Serial.println("\n--- Sending Telemetry to Edge Service ---");
    Serial.print("URL: ");
    Serial.println(edgeServiceUrl);
    Serial.print("Payload: ");
    Serial.println(jsonPayload);
    
    // Start HTTP connection
    httpClient.begin(edgeServiceUrl);
    
    // Set headers
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.addHeader("X-Device-Id", deviceId);
    httpClient.addHeader("X-API-Key", apiKey);
    
    // Send POST request
    int httpResponseCode = httpClient.POST(jsonPayload);
    
    // Check response (accept both 200 OK and 201 Created)
    if (httpResponseCode == 200 || httpResponseCode == 201) {
        String response = httpClient.getString();
        Serial.println("✓ Telemetry sent successfully!");
        Serial.print("Response: ");
        Serial.println(response);
        
        // Parse response to show details (only works with Edge Service, not Beeceptor)
        JsonDocument responseDoc;
        DeserializationError error = deserializeJson(responseDoc, response);
        
        if (!error && responseDoc.containsKey("data")) {
            Serial.print("  - Reading ID: ");
            Serial.println(responseDoc["data"]["id"].as<int>());
            Serial.print("  - Severity: ");
            Serial.println(responseDoc["data"]["severity"].as<String>());
            Serial.print("  - Backend Synced: ");
            Serial.println(responseDoc["data"]["backend_synced"].as<bool>() ? "Yes" : "No");
        }
        
        httpClient.end();
        return true;
    } else {
        Serial.print("✗ HTTP Error: ");
        Serial.println(httpResponseCode);
        
        if (httpResponseCode > 0) {
            String response = httpClient.getString();
            Serial.print("Response: ");
            Serial.println(response);
        } else {
            Serial.println("Connection failed. Check:");
            Serial.println("  1. Edge Service is running (python app.py)");
            Serial.println("  2. URL is correct (check your computer's IP)");
            Serial.println("  3. Network is accessible from Wokwi/ESP32");
        }
        
        httpClient.end();
        return false;
    }
}
