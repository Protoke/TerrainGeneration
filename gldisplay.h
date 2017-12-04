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

    void loadFile(QTextStream& file);

//    void saveAs(QTextStream& out);

//    void reset();

protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    Mesh m_mesh;
    unsigned int m_display_mode;

    float m_angleX;
    float m_angleY;
    QPoint m_position;
    
signals:
    
public slots:
    
};

#endif // GLDISPLAY_H
