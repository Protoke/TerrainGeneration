#include "heightfield.h"

bool HeightField::inside(const Vec3 &p){
    return p.z < value(p.x, p.y);
}
