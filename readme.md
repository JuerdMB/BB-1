# BB-1 Self-Balancing Robot

BB-1 is a self-balancing robot developed by Juerd Mispelblom Beyer. This project aims to create a two-wheeled robot that can maintain its balance autonomously using sensor data and motor control algorithms implemented on an ESP32 microcontroller.

## Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Features

- **Self-Balancing Mechanism**: Utilizes an Inertial Measurement Unit (IMU) for real-time orientation sensing.
- **Motor Control System**: Implements PID control algorithms for balancing, heading, and speed adjustments.
- **FreeRTOS Multitasking**: Uses FreeRTOS for concurrent task management, separating sensor reading and motor control.
- **Modular Codebase**: Organized structure for easy maintenance and scalability.
- **Configurable Logging**: Customizable logging system for debugging and monitoring.

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

### 1. Install PlatformIO

- **Option 1**: Install PlatformIO IDE.
- **Option 2**: Use PlatformIO as an extension in Visual Studio Code.

[PlatformIO Installation Guide](https://platformio.org/install)

### 2. Clone the Repository

```bash
git clone https://github.com/yourusername/BB-1.git
cd BB-1
```

### 3. Open the Project

- Open PlatformIO IDE or Visual Studio Code.
- Navigate to **File** > **Open Folder** and select the `BB-1` project folder.

### 4. Configure `platformio.ini`

Ensure the `platformio.ini` file is configured for your specific ESP32 board. Update the environment settings if necessary.

### 5. Build the Project

- Click on the **Build** icon (checkmark) in PlatformIO to compile the project.
- Resolve any dependency issues by installing missing libraries via PlatformIO's Library Manager.

### 6. Upload the Firmware

- Connect your ESP32 board to your computer via USB.
- Click on the **Upload** icon (arrow) in PlatformIO to flash the firmware onto the ESP32.

## Usage

### Hardware Assembly

1. **Connect the IMU**: Wire the IMU sensor to the ESP32 using the appropriate GPIO pins as defined in `config.h`.
2. **Set Up the Motors**: Connect the motors to the motor driver, and then connect the motor driver to the ESP32.
3. **Power Supply**: Ensure that both the ESP32 and the motors have adequate power.

### Running the Robot

1. **Power On**: Turn on the power supply to the ESP32 and the motor driver.
2. **Monitor Output**: Open the serial monitor in PlatformIO at a baud rate of `115200` to view logs.
3. **Balancing Test**: Place the robot on a flat surface and observe if it maintains balance.
4. **Adjustments**: If the robot doesn't balance correctly, you may need to tune the PID parameters.

### PID Tuning

- The PID controllers are defined in `PID.h` and instantiated in `MotorController`.
- Adjust the constants for `kp`, `ki`, and `kd` to fine-tune performance.

Contributions are welcome! Please open an issue or submit a pull request for any improvements or fixes.

---

*Note: Replace placeholders like `yourusername`, `your.email@example.com`, and adjust links as necessary before using this README.*
