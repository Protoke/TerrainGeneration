#include "heightfield.h"

bool HeightField::inside(const Vec3 &p){
    return p.z < height(p.x, p.y);
}

Vec3 HeightField::normal(int i, int j){
    throw std::logic_error("Not implemented");
    return Vec3();
}

Vec3 HeightField::normal(double x, double y){
    throw std::logic_error("Not implemented");
    return Vec3();
}
