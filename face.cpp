#include "face.h"
#include <iomanip>

Face::Face()
{
    v[0] = -1;
    v[1] = -1;
    v[2] = -1;
}

Face::Face(int v0, int v1, int v2) {
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
}

bool operator== (const Face& f1, const Face& f2) {
    return f1.v[0] == f2.v[0] && f1.v[1] == f2.v[1] && f1.v[2] == f2.v[2];
}
