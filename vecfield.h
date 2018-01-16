#ifndef VECFIELD_H
#define VECFIELD_H

#include "vec.h"
#include "array.h"
#include "scalarfield.h"

class ScalarField;

class VecField : public Array2
{
public:
    VecField();
    VecField(const Box2& b, int nx, int ny);

    virtual void display() const = 0;
    virtual ScalarField length() const = 0;
};

class Vec2Field : public VecField
{
public:
    Vec2Field();
    Vec2Field(const Box2& b, int nx, int ny);

    void setValue(int i, int j, const Vec2& v);
    Vec2 value(int i, int j) const;

    void display() const;
    ScalarField length() const;

protected:
    QVector<Vec2> m_v;
};

#endif // VECFIELD_H
