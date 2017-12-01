#include "vec.h"

#include "qmath.h"

Vec2::Vec2() : x(0.0), y(0.0) { }
Vec2::Vec2(double x, double y) : x(x), y(y) { }
Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) { }
Vec2::Vec2(const Vec3& v) : x(v.x), y(v.y) { }

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) { }
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) { }
Vec3::Vec3(const Vec2& v, double z) : x(v.x), y(v.y), z(z) { }
Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) { }

Point2::Point2() : Vec2() { }
Point2::Point2(double x, double y) : Vec2(x, y) { }
Point2::Point2(const Vec2& v) : Vec2(v) { }
Point2::Point2(const Vec3& v) : Vec2(v) { }
Point2::Point2(const Point2& p) : Vec2(p.x, p.y) { }
Point2::Point2(const Point3& p) : Vec2(p.x, p.y) { }

Point3::Point3() : Vec3() { }
Point3::Point3(double x, double y, double z) : Vec3(x, y, z) { }
Point3::Point3(const Vec2& v, double z) : Vec3(v, z) { }
Point3::Point3(const Vec3& v) : Vec3(v) { }
Point3::Point3(const Point2& p, double z) : Vec3(p.x, p.y, z) { }
Point3::Point3(const Point3& p) : Vec3(p.x, p.y, p.z) { }

double Vec2::length() {
	return qSqrt(x * x + y * y);
}

double Vec3::length() {
	return qSqrt(x * x + y * y + z * z);
}

Vec2 operator+ (const Vec2& v1, const Vec2& v2) {
	return Vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec2 operator+ (const Point2& p, const Vec2& v) {
	return Vec2(p.x + v.x, p.y + v.y);
}

Vec2 operator- (const Vec2& v1, const Vec2& v2) {
	return Vec2(v1.x - v2.x, v1.y - v2.y);
}

Vec2 operator- (const Point2& p1, const Point2& p2) {
	return Vec2(p1.x - p2.x, p1.y - p2.y);
}

Vec2 operator- (const Point2& p, const Vec2& v) {
	return Vec2(p.x - v.x, p.y - v.y);
}

Vec2 operator* (const Vec2& v, double d) {
	return Vec2(v.x * d, v.y * d);
}

Vec2 operator/ (const Vec2& v, double d) {
	return Vec2(v.x / d, v.y / d);
}

Vec3 operator+ (const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 operator+ (const Point3& p, const Vec3& v) {
	return Vec3(p.x + v.x, p.y + v.y, p.z + v.z);
}

Vec3 operator- (const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3 operator- (const Point3& p1, const Point3& p2) {
	return Vec3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

Vec3 operator- (const Point3& p, const Vec3& v) {
	return Vec3(p.x - v.x, p.y - v.y, p.z - v.z);
}

Vec3 operator* (const Vec3& v, double d) {
	return Vec3(v.x * d, v.y * d, v.z * d);
}

Vec3 operator/ (const Vec3& v, double d) {
	return Vec3(v.x / d, v.y / d, v.z / d);
}


double dot(const Vec3& va, const Vec3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

Vec3 cross(const Vec3& va, const Vec3& vb) {
	return Vec3(
		va.y * vb.z - va.z * vb.y,
		va.x * vb.z - va.z * vb.x,
		va.x * vb.y - va.y * vb.x
	);
}