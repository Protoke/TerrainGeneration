#ifndef ARRAY2_H
#define ARRAY2_H

#include "box.h"

class Array2 : public Box2
{
public:
    Array2();
    Array2(const Vec2& bl, const Vec2& tr, int nx, int ny);
    Array2(const Array2& a, int nx, int ny);

    int index(int i, int j) const;
    Vec2 localCoordinates(double x, double y) const;

    Vec2 cellSize() const;

    bool isInsideDomain(int i, int j) const;
    bool isInsideDomain(double x, double y) const;

    Vec2* neighbours4(int i, int j) const;
    Vec2* neighbours8(int i, int j) const;

    int nx, ny;

    static const Vec2 next[8];
    static const double length[8];
};

#endif // ARRAY2_H
