#pragma once

#include <QVector>

#include "vec.h"

class Box2
{
public:
	Box2();
	Box2(Point2 tl, Point2 br);
	Box2(Vec2 center, Vec2 direction, Vec2 normal);
	Box2(const Box2& b);

	QVector<Point2> corners();

	Point2 center;
	Vec2 direction, normal;
};

class Box3
{
public:
	Box3();
	Box3(Vec3 tl, Vec3 br);
	Box3(Vec3 center, Vec3 x, Vec3 y, Vec3 z);
	Box3(const Box3& b);

	QVector<Point3> corners();

	Point3 center;
	Vec3 direction, normal, right;
};
