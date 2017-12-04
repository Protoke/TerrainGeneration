#ifndef HEIGHTFILED_H
#define HEIGHTFILED_H

#include "scalarfield.h"
#include "vec.h"

class HeightField : public ScalarField
{
public:
    Vec3 normal(int i, int j);
    Vec3 normal(double x, double y);

    bool inside(const Vec3& p);

//    Mesh* createMesh();
};

#endif // HEIGHTFILED_H
