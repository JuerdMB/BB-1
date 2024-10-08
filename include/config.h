#pragma once

// ESP32 GPIO Pins
#define MOTOR_LEFT_PIN 5
#define MOTOR_RIGHT_PIN 6
#define ICM_CS 5
#define ICM_SCK 18
#define ICM_MISO 19
#define ICM_MOSI 23

// Logging
#define DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG

// Orientation Filtering Constants
#define COMPLEMENTARY_FILTER_ALPHA_PITCH .05

// Delays
#define IMU_TASK_DELAY 200
#define MCS_TASK_DELAY 200

// IMU
#define ICM_INIT_MAX_RETRIES 5
#define ICM_INIT_FAILED_DELAY_MS 1000