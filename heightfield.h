#ifndef HEIGHTFILED_H
#define HEIGHTFILED_H

#include "scalarfield.h"
#include "vec.h"

class HeightField : public ScalarField
{
public:
    bool inside(const Point3& p);

//    Mesh* createMesh();
};

#endif // HEIGHTFILED_H
