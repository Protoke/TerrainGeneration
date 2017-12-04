#pragma once

class Vec {
public:
	virtual double length() = 0;
};

class Vec2;
class Vec3;
class Point2;
class Point3;

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
public:
	Point2();
	Point2(double x, double y);
	Point2(const Vec2& v);
	Point2(const Vec3& v);
	Point2(const Point2& p);
	Point2(const Point3& p);
};

class Point3 : public Vec3 {
public:
	Point3();
	Point3(double x, double y, double z);
	Point3(const Vec2& v,  double z);
	Point3(const Vec3& v);
	Point3(const Point2& p, double z);
	Point3(const Point3& p);
};

Vec2 operator+ (const Vec2& v1, const Vec2& v2);
Vec2 operator+ (const Point2& p, const Vec2& v);
Vec2 operator- (const Vec2& v1, const Vec2& v2);
Vec2 operator- (const Point2& p1, const Point2& p2);
Vec2 operator- (const Point2& p, const Vec2& v);
Vec2 operator* (const Vec2& v, double d);
Vec2 operator/ (const Vec2& v, double d);

Vec3 operator+ (const Vec3& v1, const Vec3& v2);
Vec3 operator+ (const Point3& p, const Vec3& v);
Vec3 operator- (const Vec3& v1, const Vec3& v2);
Vec3 operator- (const Point3& p1, const Point3& p2);
Vec3 operator- (const Point3& p, const Vec3& v);
Vec3 operator* (const Vec3& v, double d);
Vec3 operator/ (const Vec3& v, double d);

bool operator== (const Vec2& v1, const Vec2& v2);
bool operator== (const Vec3& v1, const Vec3& v2);
bool operator== (const Point2& p1, const Point2& p2);
bool operator== (const Point3& p1, const Point3& p2);

double dot(const Vec3& va, const Vec3& vb);
Vec3 cross(const Vec3& va, const Vec3& vb);
