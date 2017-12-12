#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec.h"

class Triangle
{
public:
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c);

    bool isTrigo();
    Vec3 normal();

    Vec3 a, b, c;
};

#endif // TRIANGLE_H
