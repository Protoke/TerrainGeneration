#ifndef RAY_H
#define RAY_H

#include "vec.h"

class Ray
{
public:
    Ray();
    Ray(Vec3 origin, Vec3 direction);

    Vec3 operator()(double d) const;

    Vec3 origin;
    Vec3 direction;
};

#endif // RAY_H
