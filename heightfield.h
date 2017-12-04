#ifndef HEIGHTFILED_H
#define HEIGHTFILED_H

#include "scalarfield.h"
#include "vec.h"

class HeightField : public ScalarField
{
public:

    bool inside(const Vec3& p);

    Vec3 normal(int i, int j);

    Vec3 normal(double i, double j);


//    Mesh* createMesh();
};

#endif // HEIGHTFILED_H
