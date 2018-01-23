#include "ray.h"

Ray::Ray() { }

Ray::Ray(Vec3 _origin, Vec3 _direction) :
    origin(_origin), direction(normalize(_direction))
{ }

Vec3 Ray::operator()(double d) const {
    return origin + direction * d;
}
