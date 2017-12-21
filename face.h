#ifndef FACE_H
#define FACE_H


class Face
{
public:
    Face();

    Face(int v0, int v1, int v2);

    int v[3];
};

bool operator== (const Face& f1, const Face& f2);

#endif // FACE_H
