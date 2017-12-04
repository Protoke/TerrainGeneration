#pragma once

class Vec {
public:
    virtual double length() const = 0;
};

class Vec2;
class Vec3;

class Vec2 : public Vec {
public:
	Vec2();
	Vec2(double x, double y);
	Vec2(const Vec2& v);
	Vec2(const Vec3& v);

    double length() const;

	double x, y;
};

class Vec3 : public Vec {
public:
	Vec3();
	Vec3(double x, double y, double z);
	Vec3(const Vec2& v, double z);
	Vec3(const Vec3& v);

    double length() const;

	double x, y, z;
};

Vec2 operator+ (const Vec2& v1, const Vec2& v2);
Vec2 operator- (const Vec2& v1, const Vec2& v2);
Vec2 operator* (const Vec2& v, double d);
Vec2 operator/ (const Vec2& v, double d);

Vec3 operator+ (const Vec3& v1, const Vec3& v2);
Vec3 operator- (const Vec3& v1, const Vec3& v2);
Vec3 operator* (const Vec3& v, double d);
Vec3 operator/ (const Vec3& v, double d);

bool operator== (const Vec2& v1, const Vec2& v2);
bool operator== (const Vec3& v1, const Vec3& v2);

double dot(const Vec3& va, const Vec3& vb);
Vec3 cross(const Vec3& va, const Vec3& vb);

Vec3 normalize(const Vec3& v);
