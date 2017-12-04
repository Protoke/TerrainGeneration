#include "gldisplay.h"
#include <iostream>

#define FRUSTUM_SIZE 1.0f

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    m_angleX(0.0f),
    m_angleY(0.0f)
{
}

void GLDisplay::initializeGL()
{

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0, 1.0, 0.0);

    m_display_mode = 1; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(m_angleX, 0.0f, 1.0f, 0.0f);
    glRotatef(m_angleY, 1.0f, 0.0f, 0.0f);

    if(m_mesh.nbVertices() > 0 && m_mesh.nbFaces() > 0) {
        m_mesh.draw();
    }
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-FRUSTUM_SIZE, FRUSTUM_SIZE,
            -FRUSTUM_SIZE, FRUSTUM_SIZE,
            -FRUSTUM_SIZE, FRUSTUM_SIZE);

    glMatrixMode(GL_MODELVIEW);
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        QPoint position = event->pos();

        m_angleX += (position.x() - m_position.x());
        m_angleY += (position.y() - m_position.y());

        m_position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        m_position = event->pos();
}

void GLDisplay::changeDisplayMode() {
    switch (m_display_mode) {
    case 0 : m_display_mode = 1; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
    case 1 : m_display_mode = 2; glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
    case 2 : m_display_mode = 0; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    }
    updateGL();
}

void GLDisplay::loadFile(QTextStream& file) {
    m_mesh.loadOBJ(file.readAll());
    updateGL();
}

//void GLDisplay::saveAs(QTextStream& out) {
//    _triangulation.savePTS(out);
//}

//void GLDisplay::reset() {
//    _triangulation = Triangulation();
//    _crust.initialize();
//    updateGL();
//}
