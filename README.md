# Smart Edge Embedded App Example (C++ Edition)

**Version**: 0.1
**Author**: Metasoft Development Team
**Date**: November 27, 2025

## Overview

<p align="justify">
This project demonstrates the usage of the Modest IoT Nano-framework (C++ Edition) v0.1 by implementing a `SmartEdgeDevice`. This device monitors temperature using a DHT22 sensor and electrical current using an ACS712 sensor (simulated with a potentiometer). It activates an LED to indicate when the current exceeds a predefined threshold, showcasing the framework’s object-oriented, event-driven, and CQRS-inspired design. This example serves as a practical illustration of how to apply the framework to a monitoring scenario.
</p>

## Prerequisites
- **Hardware**: ESP32 development board, a DHT22 sensor, a potentiometer (to simulate the ACS712), an LED with a 220Ω resistor.
- **Software**: Arduino IDE with ESP32 support, or Wokwi for simulation.
- **Dependency**: Modest IoT Nano-framework (C++ Edition) v0.1.

## Features
- **Sensor Monitoring**: Continuously reads temperature from a DHT22 sensor and current from an ACS712.
- **High-Current Indicator**: Activates an LED when the measured current surpasses a safe threshold.
- **Event-Driven**: Utilizes an internal event system to decouple high-current detection from the LED activation logic.
- **Modular Design**: Demonstrates the use of custom sensors (`EnvironmentSensor`, `CurrentSensor`), actuators (`Led`), and a central `Device` class (`SmartEdgeDevice`) in a structured manner.
- **Simulation Support**: Fully runnable on Wokwi for easy testing and demonstration.

## Installation


<p align="justify">
1. <b>Framework</b>: This project already includes the necessary framework files.
</p>


<p align="justify">
2. <b>Project Structure</b>: The project follows a flat structure, keeping all source and header files in the root directory for simplicity and compatibility with the Arduino IDE.
</p>

```planetext
smart-edge-embedded-app/
├── SmartEdgeDevice.h
├── SmartEdgeDevice.cpp
├── EnvironmentSensor.h
├── EnvironmentSensor.cpp
├── CurrentSensor.h
├── CurrentSensor.cpp
├── Led.h
├── Led.cpp
├── ModestIoT.h
├── Device.h
├── Device.cpp
├── Sensor.h
├── Sensor.cpp
├── Actuator.h
├── Actuator.cpp
├── EventHandler.h
├── CommandHandler.h
├── sketch.ino
├── diagram.json
├── libraries.txt
└── README.md
```
