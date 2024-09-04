#include <AUnit.h>
#include "IMU.h"

test(IMUInitialization) {
    IMU imu;
    bool result = imu.initialize();
    assertTrue(result);
}

test(IMUUpdate) {
    IMU imu;
    imu.initialize();
    bool result = imu.update(0.01);
    assertTrue(result);
}

void setup() {
    Serial.begin(115200);
    aunit::TestRunner::run();
}

void loop() {
    // Empty loop as tests run in setup
}
