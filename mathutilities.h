#ifndef MATHUTILITIES_H
#define MATHUTILITIES_H

#include "vec.h"

/* Cast */
int integer(double v);

/* Random */
void randSeed();
double randDouble(double min = 0.0, double max = 1.0);

/* Geometry */
bool intersectCircles(const Vec2& ca, double ra, const Vec2& cb, double rb);

#endif // MATHUTILITIES_H
