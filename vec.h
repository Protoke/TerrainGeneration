﻿#pragma once

#include <iostream>
#include <QTextStream>

using namespace std;

/**
 * @brief Classe abstraite de vecteur.
 */
class Vec {
public:
    /**
     * @brief Calcule la norme du vecteur.
     */
    virtual double length() const = 0;
};

class Vec2;
class Vec3;

/**
 * @brief Vecteur à 2 dimensions.
 */
class Vec2 : public Vec {
public:
	Vec2();
	Vec2(double x, double y);
	Vec2(const Vec2& v);
	Vec2(const Vec3& v);

    double length() const;

	double x, y;
};

/**
 * @brief Vecteur à 3 dimensions.
 */
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
Vec2 operator* (double d, const Vec2& v);
Vec2 operator/ (const Vec2& v, double d);

Vec3 operator+ (const Vec3& v1, const Vec3& v2);
Vec3 operator- (const Vec3& v1, const Vec3& v2);
Vec3 operator* (const Vec3& v, double d);
Vec3 operator* (double d, const Vec3& v);
Vec3 operator/ (const Vec3& v, double d);

bool operator== (const Vec2& v1, const Vec2& v2);
bool operator== (const Vec3& v1, const Vec3& v2);

inline ostream& operator<<(ostream& os, const Vec2& v)
{
    os << "(" << v.x << ';' << v.y << ")";
    return os;
}
inline ostream& operator<<(ostream& os, const Vec3& v)
{
    os << "(" << v.x << ';' << v.y << ';' << v.z << ")";
    return os;
}
inline QTextStream& operator<<(QTextStream& os, const Vec3& v)
{
    os << v.x << ' ' << v.y << ' ' << v.z;
    return os;
}

double dot(const Vec3& va, const Vec3& vb);
Vec3 cross(const Vec3& va, const Vec3& vb);

Vec2 normalize(const Vec2& v);
Vec3 normalize(const Vec3& v);

/**
 * @brief Opérateur de comparaison de deux vecteurs. La comparaison se fait uniquement sur la composante z.
 */
bool operator< (const Vec3& v1, const Vec3& v2);

/**
 * @brief Génère un vecteur 2D de coordonnées x entre minX et maxX et y entre minY et maxY.
 */
Vec2 randVec2(double minX = 0.0, double minY = 0.0,
              double maxX = 1.0, double maxY = 1.0);
