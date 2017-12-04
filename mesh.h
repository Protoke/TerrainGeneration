#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QString>

#include "vec.h"

// TODO : FACES
class Face{
public:
    int v[3];
};

bool operator== (const Face& f1, const Face& f2);

class Mesh
{
public:
    Mesh();

    bool loadOBJ(const QString& filename);
    bool saveOBJ();

    int getId(const Point3& p);
    int getId(const Face& f);
    Point3& vertex(int id);
    Face& face(int id);
    int nbVertices();
    int nbFaces();

    void draw();

private:
    QVector<Face> m_faces;
    QVector<Point3> m_vertices;
};

#endif // MESH_H
