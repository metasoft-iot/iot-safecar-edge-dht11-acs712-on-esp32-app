# Smart Edge (Motor) Embedded App - IoT SafeCar

Application embebida para ESP32 ubicado en el MOTOR del vehículo. Monitorea temperatura, humedad y corriente eléctrica, enviando datos al SafeCar Edge Service para análisis predictivo.

## 🔧 Componentes

- **DHT22**: Sensor de temperatura y humedad del compartimento del motor
- **ACS712-05**: Sensor de corriente (efecto Hall, 0-5 Amperes)
- **LED**: Indicador de alerta de sobrecorriente

## 📡 Conectividad

Este dispositivo se conecta al **SafeCar Edge Service** vía WiFi y envía datos de telemetría cada 10 segundos mediante HTTP POST.

### Endpoint

```
POST http://<EDGE_SERVICE_IP>:5000/api/v1/telemetry/data-records
```

### Payload JSON

```json
{
  "sensor_location": "MOTOR",
  "engine_temperature_celsius": 95.0,
  "engine_humidity_percent": 45.0,
  "current_amperes": 2.5
}
```

## ⚙️ Configuración

### Para Wokwi (Simulación) - Configuración Activa

**Archivo**: `EdgeServiceClient.h` (líneas 18-30)

```cpp
// WiFi
const char* wifiSsid = "Wokwi-GUEST";
const char* wifiPassword = "";

// Edge Service URL - CAMBIAR POR TU IP LOCAL
String edgeServiceUrl = "http://192.168.1.100:5000/api/v1/telemetry/data-records";
//                              ^^^^^^^^^^^ Cambiar esta IP
```

#### Cómo obtener tu IP:

**macOS/Linux**:
```bash
ifconfig | grep "inet "
```

**Windows**:
```bash
ipconfig
```

Busca una IP como `192.168.x.x` o `10.0.x.x`

### Para Hardware Real - Configuración Comentada

**Archivo**: `EdgeServiceClient.h` (líneas 22-24)

Para usar en ESP32 físico:

1. **Comenta** las líneas de Wokwi (18-20, 30)
2. **Descomenta** las líneas de REAL HARDWARE (22-24, 33)
3. **Cambia** SSID y password a tu red WiFi

```cpp
// WOKWI (Comentar)
// const char* wifiSsid = "Wokwi-GUEST";
// const char* wifiPassword = "";

// REAL HARDWARE (Descomentar y configurar)
const char* wifiSsid = "MI_RED_WIFI";
const char* wifiPassword = "MI_PASSWORD";
```

### Credenciales del Dispositivo

```cpp
const char* deviceId = "safecar-001";
const char* apiKey = "test-api-key-12345";
```

> **Nota**: Estas credenciales están configuradas automáticamente en el Edge Service.

## 📚 Bibliotecas Requeridas

Ver `libraries.txt`:

- DHT sensor library
- Adafruit Unified Sensor
- ACS712
- ArduinoJson

## 🚀 Uso

### 1. Iniciar Edge Service

```bash
cd /path/to/safecar-edge-service
source venv/bin/activate
python app.py
```

### 2. Configurar IP

Edita `EdgeServiceClient.h` línea 30 con tu IP local.

### 3. Cargar en Wokwi

1. Abre [Wokwi](https://wokwi.com)
2. Crea nuevo proyecto ESP32
3. Copia todos los archivos `.h`, `.cpp`, `.ino` y `libraries.txt`
4. Carga `diagram.json`
5. Inicia simulación

### 4. Observar Serial Monitor

Deberías ver:

```
Initializing Smart Edge (Motor)...
Calibration Info:
...

=== Connecting to Edge Service ===
Connecting to WiFi...
SSID: Wokwi-GUEST
..........
✓ WiFi Connected!
IP Address: 192.168.1.46
Ready to send telemetry data!
System Ready.

========================================
Sending telemetry data...
✓ Telemetry sent successfully!
  - Reading ID: 2
  - Severity: WARNING
  - Backend Synced: Yes
========================================

Temp: 95.0 C | Current (mA): 2500 | Form factor: 0.95 | Time: 1523
```

## 🔍 Troubleshooting

### WiFi no conecta

- **Wokwi**: Verifica que usas `"Wokwi-GUEST"` exactamente
- **Hardware Real**: Verifica SSID y password

### HTTP Error: -1

- Verifica que Edge Service esté corriendo
- Verifica la IP en `EdgeServiceClient.h`
- Verifica que no haya firewall bloqueando

### Lecturas de corriente incorrectas

El ACS712 requiere calibración. Verifica la salida de `printCalibration()` en setup.

## 📊 Arquitectura

```
┌─────────────────────────┐
│   SmartEdgeDevice       │
│  (Modest IoT Pattern)   │
└───────────┬─────────────┘
            │
      ┌─────┼─────┐
      │     │     │
  ┌───▼──┐ ┌▼────┐
  │ DHT22│ │ACS712│
  └──────┘ └─────┘
            │
            ▼
┌─────────────────────────┐
│  EdgeServiceClient      │
│  (WiFi + HTTP Client)   │
└───────────┬─────────────┘
            │ POST JSON
            ▼
┌─────────────────────────┐
│  SafeCar Edge Service   │
│  localhost:5000         │
└─────────────────────────┘
```

## 🔗 Integración

Este dispositivo es parte del ecosistema SafeCar IoT:

1. **ESP32 MOTOR** (este proyecto) → Lee sensores, envía datos
2. **Edge Service** → Procesa, valida, normaliza
3. **Backend SafeCar** → Almacena en MySQL, genera insights con IA
4. **Dashboard Web** → Visualiza telemetría y alertas

## ⚡ Monitoreo de Corriente

El ACS712 mide la corriente del sistema eléctrico:

- **Normal**: 1.5 - 3.5A
- **Alta** (>4.2A): Posible sobrecarga
- **Baja** (<0.4A): Posible falla de batería/alternador

El Edge Service clasifica según umbrales:
- `> 4.0A` → Severity: CRITICAL
- `> 3.5A` → Severity: WARNING
- Normal → Severity: INFO

## 📄 Licencia

MIT License - Proyecto académico MetaSoft IoT

---

**Documentación actualizada**: 27 Nov 2025  
**Versión**: 2.0 - Con integración Edge Service
