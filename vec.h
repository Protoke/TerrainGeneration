#pragma once

#include "qmath.h"

class Vec {
public:
	virtual double length() = 0;
};

class Vec3;
class Vec2;

class Vec2 : public Vec {
public:
	Vec2();
	Vec2(double x, double y);
	Vec2(const Vec2& v);
	Vec2(const Vec3& v);

	double length();

	double x, y;
};

class Vec3 : public Vec {
public:
	Vec3();
	Vec3(double x, double y, double z);
	Vec3(const Vec2& v, double z);
	Vec3(const Vec3& v);

	double length();

	double x, y, z;
};

class Point2 : public Vec2 {
	Point2();
	Point2(double x, double y);
	Point2(const Vec2& v);
	Point2(const Vec3& v);
	Point2(const Point2& p);
	Point2(const Point3& p);
};

class Point3 : public Vec3 {
	Point3();
	Point3(double x, double y, double z);
	Point3(const Vec2& v);
	Point3(const Vec3& v);
	Point3(const Point2& p);
	Point3(const Point3& p);
};

inline double dot(const Vec3& va, const Vec3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

inline Vec3 cross(const Vec3& va, const Vec3& vb) {
	return Vec3(
		va.y * vb.z - va.z * vb.y,
		va.x * vb.z - va.z * vb.x,
		va.x * vb.y - va.y * vb.x
	);
}