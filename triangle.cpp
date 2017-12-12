#include "triangle.h"

Triangle::Triangle(const Vec3& a, const Vec3& b, const Vec3& c) :
    a(a), b(b), c(c)
{ }

bool Triangle::isTrigo(){
    return normal().z > 0;
}

Vec3 Triangle::normal(){
    return cross(b-a, c-a);
}
