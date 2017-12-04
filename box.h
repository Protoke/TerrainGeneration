#pragma once

#include <QVector>

#include "vec.h"

class Box2
{
public:
	Box2();
    Box2(Point2 bl, Point2 tr);
    Box2(const Box2& b);

    Point2 bl, tr;
};
