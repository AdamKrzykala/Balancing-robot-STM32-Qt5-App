#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <GLUT/glut.h>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

private:

    int m_xRot;
    int m_yRot;
    int m_zRot;

public:

    GLWidget(QWidget *parent = nullptr);
    ~GLWidget() Q_DECL_OVERRIDE;

    //QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    //QSize sizeHint()        const Q_DECL_OVERRIDE;

public slots:

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

protected:

    void initializeGL()                         Q_DECL_OVERRIDE;
    void paintGL()                              Q_DECL_OVERRIDE;
    void resizeGL(int width, int height)        Q_DECL_OVERRIDE;
};

#endif
