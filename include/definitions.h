#pragma once

struct position3D {
    position3D(double inX, double inY, double inZ): x(inX), y(inY), z(inZ)
    {
    }

    position3D(): x(0.), y(0.), z(0.)
    {
    }

    double x;
    double y;
    double z;
};

struct orientation3D {
    double r;
    double p;
    double y;
};