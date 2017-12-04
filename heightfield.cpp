#include "heightfield.h"

bool HeightField::inside(const Vec3 &p){
    return p.z < height(p.x, p.y);
}
