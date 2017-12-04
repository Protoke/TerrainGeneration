#include "array.h"

Array2::Array2() { }

Array2::Array2(const Vec2 &bl, const Vec2 &tr, int nx, int ny) :
    Box2(bl, tr), nx(nx), ny(ny)
{ }

Array2::Array2(const Array2 &a, int nx, int ny) : Box2(a.bl, a.tr), nx(a.nx), ny(a.ny) { }

int Array2::index(int i, int j) {
    return i*ny + j;
}

Vec2 Array2::localCoordinates(double x, double y){
    return Vec2((x + bl.x) / (tr.x - bl.x),
                (y - bl.y) / (tr.y - bl.y));
}
