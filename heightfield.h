#ifndef HEIGHTFILED_H
#define HEIGHTFILED_H

#include "scalarfield.h"
#include "analyticscalarfield.h"
#include "vec.h"
#include "mesh.h"

class HeightField : public ScalarField
{
public:
    HeightField();
    HeightField(const Box2& b, int nx, int ny);
    HeightField(const AnalyticScalarField& a, const Box2& b, int nx, int ny);

    bool inside(const Vec3& p) const;

    Vec3 normal(int i, int j) const;
    Vec3 normal(double x, double y) const;

    ScalarField drainingArea() const;
    Vec2Field slope() const;
    ScalarField streamPower() const;
    ScalarField access() const;
    ScalarField wetnessIndex() const;

    int checkFlowDirections(const Vec3& p, Vec3* dumpPoints,
                            double* dumpHeight, double* dumpSlope) const;

    Mesh createMesh(int stepi = 1, int stepj = 1) const;
};

#endif // HEIGHTFILED_H
