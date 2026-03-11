# Smart Vehicle Platform  
### STM32 + Raspberry Pi + ESP32 Robotics Project

## Overview

This project is a small robotic vehicle platform built to explore embedded systems, motor control, communication, and system integration.

The system combines three main units:

- **STM32** for real-time hardware control
- **Raspberry Pi** for the user interface and higher-level logic
- **ESP32** as a Wi-Fi and MQTT communication bridge

The vehicle is controlled through a **web interface running on the Raspberry Pi**. Commands are sent over **MQTT** to the **ESP32**, which transfers them to the **STM32**. The STM32 controls the motors and reads the sensors, and can also send data back through the ESP32 to the Raspberry Pi.

This project is designed as a **learning platform for robotics, embedded systems, and multi-device communication**.


# System Architecture

```text
User (Browser)
      │
      │ WiFi / Network
      ▼
Raspberry Pi
(Web UI + Control Logic + MQTT)
      │
      │ MQTT
      ▼
ESP32
(WiFi Bridge / Communication Gateway)
      │
      │ UART
      ▼
STM32 Microcontroller
(Hardware Control)
      │
      ├── Motor Drivers
      └── Sensors
```


# Controller Roles

## STM32 (Low-Level Hardware Control)

The STM32 microcontroller handles all real-time hardware operations.

Responsibilities:

- Motor PWM control
- Motor direction control
- Ultrasonic sensor measurement
- Timing-critical operations
- Communication with ESP32

Technologies used:

- C / C++
- STM32 CMSIS
- TIM PWM
- UART communication


## Raspberry Pi (System Controller)

The Raspberry Pi acts as the system interface and higher-level control layer.

Responsibilities:

- Web-based control interface
- User input handling
- MQTT communication
- System monitoring

Technologies used:

- Python
- Flask web server
- MQTT
- Linux services


## ESP32 (Wi-Fi and MQTT Bridge)

The ESP32 works as the communication bridge between the Raspberry Pi and the STM32.

Responsibilities:

- Receive commands from Raspberry Pi over MQTT
- Forward commands to STM32
- Receive data from STM32
- Send data back to Raspberry Pi
- Provide Wi-Fi communication layer

Technologies used:

- ESP32 firmware
- MQTT client
- UART communication
- Wi-Fi networking


# Hardware Components

Main components used in the system:

- STM32F091RC (Nucleo board)
- Raspberry Pi
- ESP32
- 2 × TB6612FNG motor drivers
- 4 × DC motors
- HC-SR04 ultrasonic sensor
- Battery power system


# Project Goals

This project is used to learn and experiment with:

- Embedded programming
- Motor control
- MQTT communication
- Robotics architecture
- Hardware-software integration
- STM32 development
- Raspberry Pi system integration
- ESP32 communication bridging
