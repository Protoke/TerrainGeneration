#include "gldisplay.h"
#include <iostream>
#include "heightfield.h"
#include <QMessageBox>

#define FRUSTUM_SIZE 1.0f

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angleX(0.0f),
    _angleY(0.0f)
{
}

void GLDisplay::initializeGL()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0, 1.0, 0.0);

    _display_mode = 1; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(_angleX, 0.0f, 1.0f, 0.0f);
    glRotatef(_angleY, 1.0f, 0.0f, 0.0f);

    if(_mesh.nbVertices() > 0) {
        _mesh.draw();
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

        _angleX += (position.x() - _position.x());
        _angleY += (position.y() - _position.y());

        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _position = event->pos();
}

void GLDisplay::changeDisplayMode() {
    switch (_display_mode) {
    case 0 : _display_mode = 1; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
    case 1 : _display_mode = 2; glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
    case 2 : _display_mode = 0; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    }
    updateGL();
}

void GLDisplay::createTerrain(const QString& filename) {
    QImage img;
    // error format
    if(!img.load(filename)) {
        QMessageBox::warning(this, "Error", "No image opened.");
        return;
    }
    // no error format
    img = QImage(filename);
    HeightField hf;
    // TODO : QDialog pour entrer les parametres
    hf.load(img, Vec2(0, 0), Vec2(1024, 1024), 0, 100);
    _mesh = hf.createMesh(8,8);
    updateGL();
}

void GLDisplay::loadFile(const QString& filename) {
    _mesh.loadOBJ(filename);
    updateGL();
}

void GLDisplay::saveAs(const QString& filename) {
    _mesh.saveOBJ(filename);
    //QImage image;
    //hf.toImage(image);
    //image.save("../terrain.jpg");
}

void GLDisplay::reset() {
//    _triangulation = Triangulation();
//    _crust.initialize();
    updateGL();
}
