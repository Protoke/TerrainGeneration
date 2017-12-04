#include "mesh.h"

#include <GL/gl.h>

bool operator== (const Face& f1, const Face& f2){
    return f1.v[0] == f2.v[0] && f1.v[1] == f2.v[1] && f1.v[2] == f2.v[2];
}

bool Mesh::loadOBJ(const QString& filename){
    throw std::logic_error("Not implemented");
}

bool Mesh::saveOBJ(){
    throw std::logic_error("Not implemented");
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

Face& Mesh::face(int id){
    return m_faces[id];
}

int Mesh::nbVertices(){
    return m_vertices.size();
}

int Mesh::nbFaces(){
    return m_faces.size();
}

void Mesh::draw(){
    glLineWidth(1.0);
    glBegin(GL_TRIANGLES);
         for(int i = 0;i < m_faces.length();i++) {
             glVertex3f(m_vertices[m_faces[i].v[0]].x,
                        m_vertices[m_faces[i].v[0]].y,
                        m_vertices[m_faces[i].v[0]].z);
             glVertex3f(m_vertices[m_faces[i].v[1]].x,
                        m_vertices[m_faces[i].v[1]].y,
                        m_vertices[m_faces[i].v[1]].z);
             glVertex3f(m_vertices[m_faces[i].v[2]].x,
                        m_vertices[m_faces[i].v[2]].y,
                        m_vertices[m_faces[i].v[2]].z);
         }
    glEnd();
}

