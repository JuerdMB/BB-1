# BB-1 Self-Balancing Robot

BB-1 is a self-balancing robot developed by Juerd Mispelblom Beyer. This project aims to create a two-wheeled robot that can maintain its balance autonomously using sensor data and motor control algorithms implemented on an ESP32 microcontroller.

## Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Hardware Requirements

- **ESP32 Development Board**: The primary microcontroller for processing and control.
- **Inertial Measurement Unit (IMU)**: For example, an ICM-20948 sensor module for orientation data.
- **Motor Driver**: A suitable driver like L298N to control the motors.
- **DC Motors**: Two identical motors for movement.
- **Power Supply**: Adequate power source for both the ESP32 and the motors.
- **Additional Components**: Wires, connectors, chassis, and other assembly parts.

## Software Requirements

- **PlatformIO Core (CLI) or PlatformIO IDE**: For building and uploading the firmware.
- **Arduino Framework**: The base framework used with PlatformIO for ESP32 development.
- **FreeRTOS**: Included in the ESP32 Arduino core for task management.
- **Serial Monitor**: For logging output (built into PlatformIO or use an external tool).

## Installation and Setup

### Hardware Assembly

1. **Connect the IMU**: Wire the IMU sensor to the ESP32 using the appropriate GPIO pins as defined in `config.h`.
2. **Set Up the Motors**: Connect the motors to the motor driver, and then connect the motor driver to the ESP32.
3. **Power Supply**: Ensure that both the ESP32 and the motors have adequate power.

### PID Tuning

- The PID controllers are defined in `PID.h` and instantiated in `MotorController`.
- Adjust the constants for `kp`, `ki`, and `kd` to fine-tune performance.

Contributions are welcome! Please open an issue or submit a pull request for any improvements or fixes.