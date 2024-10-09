#pragma once

class MotionController
{
public:
    MotionController();
    void computeAdjustedPitchAngle();
    void publishAdjustedPitchAngle();
};
