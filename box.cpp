#include "box.h"

Box2::Box2() { }

Box2::Box2(Point2 tl, Point2 br) 
{ 
	direction = Vec2((tl.x - br.x) / 2.0, 0.0);
	normal = Vec2(0.0, (tl.y - br.y) / 2.0);
	center = tl + direction + normal;
}

Box2::Box2(Vec2 center, Vec2 direction, Vec2 normal) : 
	center(center), 
	direction(direction), 
	normal(normal) 
{ }

Box2::Box2(const Box2& b) : 
	center(b.center), 
	direction(b.direction), 
	normal(b.normal) 
{ }

QVector<Point2> Box2::corners() {
	QVector<Point2> corners;

	corners.push_back(Point2(center - direction - normal));
	corners.push_back(Point2(center + direction - normal));
	corners.push_back(Point2(center + direction + normal));
	corners.push_back(Point2(center - direction + normal));

	return corners;
}

Box3::Box3() { }

Box3::Box3(Vec3 tl, Vec3 br) 
{ 
	direction = Vec3((tl.x - br.x) / 2.0, 0.0, 0.0);
	normal = Vec3(0.0, (tl.y - br.y) / 2.0, 0.0);
	right = Vec3(0.0, 0.0, (tl.z - br.z) / 2.0);
	center = tl + direction + normal + right;
}

Box3::Box3(Vec3 center, Vec3 direction, Vec3 normal, Vec3 right) : 
	center(center), 
	direction(direction), 
	normal(normal), 
	right(right) 
{ }

Box3::Box3(const Box3& b) : 
	center(b.center), 
	direction(b.direction), 
	normal(b.normal), 
	right(b.right) 
{ }

QVector<Point3> Box3::corners() {
	QVector<Point3> corners;

	corners.push_back(Point3(center - direction - normal - right));
	corners.push_back(Point3(center + direction - normal - right));
	corners.push_back(Point3(center + direction + normal - right));
	corners.push_back(Point3(center - direction + normal - right));
	corners.push_back(Point3(center - direction - normal + right));
	corners.push_back(Point3(center + direction - normal + right));
	corners.push_back(Point3(center + direction + normal + right));
	corners.push_back(Point3(center - direction + normal + right));

	return corners;
}

