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

Array2::Array2(const Array2 &a, int nx, int ny) :
    Box2(a.bl, a.tr), nx(a.nx), ny(a.ny)
{ }

int Array2::index(int i, int j) {
    return i*ny + j;
}

Vec2 Array2::localCoordinates(double x, double y){
    return Vec2((x + bl.x) / (tr.x - bl.x),
                (y - bl.y) / (tr.y - bl.y));
}

Vec2 Array2::cellSize() {
    return Vec2(bl.x + (tr.x - bl.x) / nx ,
                bl.y + (tr.y - bl.y) / ny);
}

bool Array2::isInsideDomain(int i, int j){
    if(i >= 0 && i < nx-1)
        if(j >= 0 && j < ny-1)
            return true;
    return false;
}

bool Array2::isInsideDomain(double x, double y){
    if(x >= bl.x && x <= tr.x)
        if(y >= bl.y && y <= tr.y)
            return true;
    return false;
}

Vec2* Array2::neighbours4(int i, int j) {
    Vec2* neighbours = new Vec2[4];
    neighbours[0] = Vec2(i+1, j);
    neighbours[1] = Vec2(i-1, j);
    neighbours[2] = Vec2(i, j+1);
    neighbours[3] = Vec2(i, j-1);
    return neighbours;
}

Vec2* Array2::neighbours8(int i, int j) {
    Vec2* n8 = new Vec2[4];;
    n8[0] = Vec2(i+1, j);
    n8[1] = Vec2(i-1, j);
    n8[2] = Vec2(i, j+1);
    n8[3] = Vec2(i, j-1);
    n8[4] = Vec2(i+1, j+1);
    n8[5] = Vec2(i-1, j-1);
    n8[6] = Vec2(i-1, j+1);
    n8[7] = Vec2(i+1, j-1);
    return n8;
}
