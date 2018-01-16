#ifndef VECFIELD_H
#define VECFIELD_H

#include "vec.h"
#include "array.h"

class VecField : public Array2
{
public:
    VecField();
    VecField(const Box2& b, int nx, int ny);

    virtual void display() const = 0;
};

class Vec2Field;
//class Vec3Field;

class Vec2Field : public VecField
{
public:
    Vec2Field();
    Vec2Field(const Box2& b, int nx, int ny);

    void setValue(int i, int j, const Vec2& v);
    Vec2 value(int i, int j) const;

    void display() const;

protected:
    QVector<Vec2> m_v;
};

//class Vec3Field : public VecField
//{
//    Vec3Field();
//    Vec3Field(const Box2& b, int nx, int ny);

//protected:
//    QVector<Vec3> m_v;
//};

#endif // VECFIELD_H
