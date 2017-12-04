#pragma once

#include <QVector>

#include "vec.h"

class Box2
{
public:
	Box2();
    Box2(const Vec2& bl, const Vec2& tr);
    Box2(const Box2& b);

    Vec2 bl, tr;
};
