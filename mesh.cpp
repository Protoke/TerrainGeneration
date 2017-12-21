#include "mesh.h"

#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>

#include <GL/gl.h>

using namespace std;

bool operator== (const Face& f1, const Face& f2){
    return f1.v[0] == f2.v[0] && f1.v[1] == f2.v[1] && f1.v[2] == f2.v[2];
}

bool Mesh::loadOBJ(const QString& filename){
    throw std::logic_error("Not implemented");
}

bool Mesh::saveOBJ(const QString& filename){
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

    QVectorIterator<Face> itf(m_faces);
    while(itf.hasNext()){
        Face f = itf.next();
        stream << "f " << f.v[0]+1 << " " << f.v[1]+1 << " " << f.v[2]+1 << endl;
    }
    stream << endl;

    return true;
}

int Mesh::getId(const Vec3& p){
    for(int i = 0; i < m_vertices.size(); ++i){
        if(p == m_vertices[i])
            return i;
    }
    return -1;
}

int Mesh::getId(const Face& f){
    for(int i = 0; i < m_faces.size(); ++i){
        if(f == m_faces[i])
            return i;
    }
    return -1;
}

Vec3& Mesh::vertex(int id){
    return m_vertices[id];
}

Vec3& Mesh::vertex(int idFace, int idInFace) {
    if(idFace < 0 || idFace > nbFaces()-1 || idInFace < 0 || idInFace > 2) {
        throw std::invalid_argument("Id incorrect");
    }
    return m_vertices[m_faces[idFace].v[idInFace]];
}

Face& Mesh::face(int id){
    return m_faces[id];
}

int Mesh::nbVertices(){
    return m_vertices.size();
}

int Mesh::nbFaces(){
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

void Mesh::draw(){
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

