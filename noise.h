#ifndef NOISE_H
#define NOISE_H

#include "vec.h"

class Noise
{
public:
    virtual double value(const Vec2& p) const = 0;
};

class SimplexNoise : public Noise
{
public:
    double value(const Vec2& p) const;

protected:
    static const int grad2[8][2];
    static const int perm[512];

    double dot(const int* g, const double& x, const double& y) const;
};

#endif // NOISE_H
