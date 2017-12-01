#pragma once

#include "vec.h"

class Box {
	
};

class Box2 : Box
{
public:
	Box2();
	Box2(Vec2 tl, Vec2 br);
	Box2(Vec2 center, Vec2 x, Vec2 y);
	Box2(const Box2& b);

	Point2 center;
	Vec2 direction;
};

class Box3 : Box
{
public:
	Box3();
	Box3(Vec2 tl, Vec2 br);
	Box3(Vec3 center, Vec3 x, Vec3 y, Vec3 z);
	Box3(const Box3& b);

	Point3 center;
	Vec3 direction, normal;
};
