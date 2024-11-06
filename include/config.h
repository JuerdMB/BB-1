#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#endif

// ESP32 GPIO Pins
constexpr uint8_t MOTOR_LEFT_A   = 36;
constexpr uint8_t MOTOR_LEFT_B   = 39;
constexpr uint8_t MOTOR_RIGHT_A   = 34;
constexpr uint8_t MOTOR_RIGHT_B   = 35;
constexpr uint8_t ICM_CS            = 5;    // NCS
constexpr uint8_t ICM_SCK           = 18;   // SCLK
constexpr uint8_t ICM_MISO          = 19;   // SDO
constexpr uint8_t ICM_MOSI          = 23;   // SDI
constexpr uint8_t ICM_INTERRUPT     = 13;

// Logging
constexpr uint8_t DEFAULT_LOG_LEVEL = 0;
constexpr uint16_t LOGGER_MESSAGE_QUEUE_SIZE = 100; // Size of message buffer
constexpr TickType_t LOGGER_ENQUEUE_TIMEOUT = 0;    // How many ticks to wait before discarting the message when queue is full

// Orientation Filtering Constants
constexpr float COMPLEMENTARY_FILTER_PITCH_ALPHA = .05;

// Control loop frequencies (Hz)
constexpr uint16_t BALANCING_CONTROL_FREQUENCY = 200;
constexpr uint16_t MOTION_CONTROL_FREQUENCY = 50;
constexpr uint16_t ENCODER_READING_FREQUENCY = 100;

// IMU
// #define IMU_USE_INTERRUPT
constexpr uint8_t ICM_INIT_MAX_RETRIES = 5;
constexpr uint16_t ICM_INIT_FAILED_DELAY_MS = 1000;

// Task priorities
constexpr uint8_t BALANCING_CONTROLLER_TASK_PRIORITY = 5;
constexpr uint8_t IMU_READER_TASK_PRIORITY = 6;
constexpr uint8_t MOTION_CONTROLLER_TASK_PRIORITY = 3;
constexpr uint8_t ENCODER_READING_TASK_PRIORITY = 3;
constexpr uint8_t COMMUNICATION_TASK_PRIORITY = 2;
constexpr uint8_t DIAGNOSTICS_TASK_PRIORITY = 1;

// Task stack sizes
constexpr uint16_t TASK_STACK_SIZE = 4096;

// Physical constants
constexpr float WHEEL_BASE = 0.15f; // Distance between wheels in meters

// Motor constants
constexpr int MOTORS_MIN_SPEED = -255;
constexpr int MOTORS_MAX_SPEED = 255;