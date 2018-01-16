#include "mesh.h"

#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>

#include <GL/gl.h>

using namespace std;

bool Mesh::loadOBJ(const QString& filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QTextStream ts(&file);

    m_faces.clear();
    m_vertices.clear();
    m_vMin = Vec3();
    m_vMax = Vec3();

    char element;
    float x, y, z;
    ts >> element;

    while(element == '\n' || element == '#')
        ts >> element;

    // 1ere passe pour initialiser les sommets min et max
    if(element == 'v') {
        ts >> x;
        ts >> y;
        ts >> z;
        Vec3 vertex(x, y, z);
        m_vertices.push_back(vertex);
        m_vMin = vertex;
        m_vMax = vertex;
        ts >> element;
        while(element == '\n' || element == '#')
            ts >> element;
    }

    while(element == 'v') {
        ts >> x;
        ts >> y;
        ts >> z;
        m_vertices.push_back(Vec3(x, y, z));

        // update min/max vertices
        if(m_vMin.x > x)
            m_vMin.x = x;
        if(m_vMax.x < x)
            m_vMax.x = x;

        if(m_vMin.y > y)
            m_vMin.y = y;
        if(m_vMax.y < y)
            m_vMax.y = y;

        if(m_vMin.z > z)
            m_vMin.z = z;
        if(m_vMax.z < z)
            m_vMax.z = z;

        ts >> element;
        while(element == '\n' || element == '#')
            ts >> element;
    }

    // TODO : lire les normales

    while(element == 'f') {
        int v1, v2, v3;
        ts >> v1;
        ts >> v2;
        ts >> v3;
        m_faces.push_back(Face(v1-1, v2-1, v3-1));
        ts >> element;
        while(element == '\n' || element == '#')
            ts >> element;
    }

    file.close();
    return true;
}

bool Mesh::saveOBJ(const QString& filename) const {
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite)){
        return false;
    }

    file.resize(0);

    QTextStream stream(&file);

    QVectorIterator<Vec3> itv(m_vertices);
    while(itv.hasNext()){
        stream << "v " << itv.next() << endl;
    }
    stream << endl;

    // TODO : ecrire les normales

    QVectorIterator<Face> itf(m_faces);
    while(itf.hasNext()){
        Face f = itf.next();
        stream << "f " << f.v[0]+1 << " " << f.v[1]+1 << " " << f.v[2]+1 << endl;
    }
    stream << endl;

    return true;
}

int Mesh::getId(const Vec3& p) const {
    for(int i = 0; i < m_vertices.size(); ++i){
        if(p == m_vertices[i])
            return i;
    }
    return -1;
}

int Mesh::getId(const Face& f) const {
    for(int i = 0; i < m_faces.size(); ++i){
        if(f == m_faces[i])
            return i;
    }
    return -1;
}

Vec3 Mesh::vertex(int id) const {
    return m_vertices[id];
}

Vec3 Mesh::vertex(int idFace, int idInFace) const {
    if(idFace < 0 || idFace > nbFaces()-1 || idInFace < 0 || idInFace > 2) {
        throw std::invalid_argument("Id incorrect");
    }
    return m_vertices[m_faces[idFace].v[idInFace]];
}

Face Mesh::face(int id) const {
    return m_faces[id];
}

int Mesh::nbVertices() const {
    return m_vertices.size();
}

int Mesh::nbFaces() const{
    return m_faces.size();
}

void Mesh::addVertex(const Vec3& v){
    m_vertices.push_back(v);
}

void Mesh::addFace(const Face& f){
    m_faces.push_back(f);
}

void Mesh::setMax(Vec3 vertex) {
    m_vMax = vertex;
}

void Mesh::setMin(Vec3 vertex) {
    m_vMin = vertex;
}

void Mesh::draw() const {
    glLineWidth(1.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);

        // vertices normalization between -minCible and maxCible
        // (originale - MIN) * (maxCible - minCible) / (MAX - MIN) + minCible

        // dezoome
        Vec3 min(-0.8f, -0.8f, -0.8f);
        Vec3 max(0.8f, 0.8f, 0.8f);

         for(int i = 0;i < m_faces.length();i++) {
             glVertex3f((vertex(i, 0).x - m_vMin.x) * (max.x - min.x) / (m_vMax.x - m_vMin.x) + min.x,
                        (vertex(i, 0).y - m_vMin.y) * (max.y - min.y) / (m_vMax.y - m_vMin.y) + min.y,
                        (vertex(i, 0).z - m_vMin.z) * (max.z - min.z) / (m_vMax.z - m_vMin.z) + min.z);
             glVertex3f((vertex(i, 1).x - m_vMin.x) * (max.x - min.x) / (m_vMax.x - m_vMin.x) + min.x,
                        (vertex(i, 1).y - m_vMin.y) * (max.y - min.y) / (m_vMax.y - m_vMin.y) + min.y,
                        (vertex(i, 1).z - m_vMin.z) * (max.z - min.z) / (m_vMax.z - m_vMin.z) + min.z);
             glVertex3f((vertex(i, 2).x - m_vMin.x) * (max.x - min.x) / (m_vMax.x - m_vMin.x) + min.x,
                        (vertex(i, 2).y - m_vMin.y) * (max.y - min.y) / (m_vMax.y - m_vMin.y) + min.y,
                        (vertex(i, 2).z - m_vMin.z) * (max.z - min.z) / (m_vMax.z - m_vMin.z) + min.z);
         }

    glEnd();
}

