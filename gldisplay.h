#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QTextStream>
#include "mesh.h"

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);

    void changeDisplayMode();

    void createTerrain(const QString& filename);

    void loadFile(const QString& filename);

    void saveAs(const QString& filename);

    void reset();

protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    //void drawSierpinski();
    unsigned int _display_mode;

    float _angleX;
    float _angleY;
    QPoint _position;
    Mesh _mesh;

signals:

public slots:

};

#endif // GLDISPLAY_H
