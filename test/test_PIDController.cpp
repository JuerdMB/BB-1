#include <AUnit.h>
#include "PIDController.h"

test(PIDCompute) {
    PIDController pid(1.0, 0.1, 0.01);
    float output = pid.compute(0.0, 10.0, 0.1);
    assertTrue(output > 0);
}

test(PIDSetTunings) {
    PIDController pid(1.0, 0.1, 0.01);
    pid.setTunings(2.0, 0.2, 0.02);
    float output = pid.compute(0.0, 10.0, 0.1);
    assertTrue(output > 0);
}

void setup() {
    Serial.begin(115200);
    aunit::TestRunner::run();
}

void loop() {
    // Empty loop as tests run in setup
}
