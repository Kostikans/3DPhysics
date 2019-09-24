#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include "camera.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include "sphere.h"
#include "floor.h"
#include "light.h"
#include <QTime>
#include <QVector>


#include "collisiondetector.h"


class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
private:
    void initShaders();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void handlePlayerInput(int key, bool isPressed);
    void moveCamera();

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLShaderProgram m_shaderLightProgram;
    QOpenGLTexture *m_texture;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLBuffer m_arrayBuffer;
    Camera *m_Camera;
    QVector2D m_previousMousePos;
    bool WKey,SKey,AKey,DKey;
    SphereObj *sphere1;
    SphereObj *sphere2;
    Floor *floor;
    Light *light;
    float deltaTime;
    QVector<SphereObj*> objects;

    CollisionDetector collisionDetector;



};

#endif // WIDGET_H
