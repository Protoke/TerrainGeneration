#include "heightfield.h"

bool HeightField::inside(const Point3 &p){
    return p.z < height(p.x, p.y);
}
