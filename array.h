#ifndef ARRAY2_H
#define ARRAY2_H

#include "box.h"

class Array2 : public Box2
{
public:
    Array2();
    Array2(const Vec2& bl, const Vec2& tr, int nx, int ny);
    Array2(const Array2& a, int nx, int ny);

    int index(int i, int j);
    Vec2 localCoordinates(double x, double y);

    Vec2 cellSize();

    bool isInsideDomain(int i, int j);
    bool isInsideDomain(double x, double y);

    Vec2* neighbours4(int i, int j);
    Vec2* neighbours8(int i, int j);

    int nx, ny;
};

#endif // ARRAY2_H
