#include "array.h"

#include <qmath.h>

const Vec2 Array2::next[8]= {
    Vec2(-1, 0),
    Vec2(-1, -1),
    Vec2(0, -1),
    Vec2(1, -1),
    Vec2(1, 0),
    Vec2(1, 1),
    Vec2(0, 1),
    Vec2(-1, 1)
};

const double Array2::length[8] = {
    1.0,
    qSqrt(2),
    1.0,
    qSqrt(2),
    1.0,
    qSqrt(2),
    1.0,
    qSqrt(2)
};

Array2::Array2() { }

Array2::Array2(const Vec2 &bl, const Vec2 &tr, int nx, int ny) :
    Box2(bl, tr), nx(nx), ny(ny)
{ }

Array2::Array2(const Array2 &a) :
    Box2(a.bl, a.tr), nx(a.nx), ny(a.ny)
{ }

int Array2::index(int i, int j) const {
    return j*ny + i;
}

Vec2 Array2::localCoordinates(double x, double y) const {
    return Vec2((x - bl.x) / (tr.x - bl.x),
                (y - bl.y) / (tr.y - bl.y));
}

Vec2 Array2::cellSize() const {
    return Vec2(bl.x + (tr.x - bl.x) / nx ,
                bl.y + (tr.y - bl.y) / ny);
}

bool Array2::isInsideDomain(int i, int j) const {
    if(i >= 0 && i < nx)
        if(j >= 0 && j < ny)
            return true;
    return false;
}

bool Array2::isInsideDomain(double x, double y) const {
    if(x >= bl.x && x <= tr.x)
        if(y >= bl.y && y <= tr.y)
            return true;
    return false;
}
