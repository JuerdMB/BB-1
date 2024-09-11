struct vec3 {
    vec3(double inX, double inY, double inZ): x(inX), y(inY), z(inZ)
    {
    }

    vec3(): x(0.), y(0.), z(0.)
    {
    }

    double x;
    double y;
    double z;
};

struct orientation3 {
    double r;
    double p;
    double y;
};