/**
 * @file sketch.ino
 * @brief Main entry point for the Smart Edge (Motor) application.
 * 
 * Re-structured to follow the Modest IoT Nano-framework pattern.
 * Logic is delegated to the SmartEdgeDevice class.
 */

#include "ModestIoT.h"
#include "SmartEdgeDevice.h"

SmartEdgeDevice device; ///< Instance of the SmartEdgeDevice.

void setup() {
    Serial.begin(115200);
    device.setup();
}

void loop() {
    device.update();
    delay(100); 
}
