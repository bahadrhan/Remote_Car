#pragma once

// ===== UART (ESP32 ↔ STM32) =====
#define STM_UART_NUM   1
#define STM_UART_RX    26
#define STM_UART_TX    25
#define STM_UART_BAUD  115200

// ===== MQTT =====
#define MQTT_BROKER    "192.168.178.107"
#define MQTT_PORT      1883
#define TOPIC_CMD      "car/cmd"
#define TOPIC_TEL      "car/telemetry"

// ===== WiFi =====
#define WIFI_SSID      ""
#define WIFI_PASS      ""
