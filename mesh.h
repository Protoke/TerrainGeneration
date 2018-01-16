#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QString>

#include "vec.h"
#include "face.h"

class Mesh
{
public:
    bool loadOBJ(const QString& filename);
    bool saveOBJ(const QString& filename) const;

    int getId(const Vec3& p) const;
    int getId(const Face& f) const;
    Vec3 vertex(int id) const;
    Vec3 vertex(int idFace, int idInFace) const;
    Face face(int id) const;
    int nbVertices() const;
    int nbFaces() const;
    void addVertex(const Vec3& v);
    void addFace(const Face& f);
    void setMax(Vec3 vertex);
    void setMin(Vec3 vertex);

    void draw() const;

private:
    QVector<Face> m_faces;
    QVector<Vec3> m_vertices;
    Vec3 m_vMin;
    Vec3 m_vMax;
};

#endif // MESH_H
