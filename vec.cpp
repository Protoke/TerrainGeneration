#include "vec.h"

Vec2::Vec2() : x(0.0), y(0.0) { }
Vec2::Vec2(double x, double y) : x(x), y(y) { }
Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) { }
Vec2::Vec2(const Vec3& v) : x(v.x), y(v.y) { }

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) { }
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) { }
Vec3::Vec3(const Vec2& v, double z) : x(v.x), y(v.y), z(z) { }
Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) { }

double Vec2::length() {
	return qSqrt(x * x + y * y);
}

double Vec3::length() {
	return qSqrt(x * x + y * y + z * z);
}