#include "widget.h"
#include <QtMath>
#include <QOpenGLContext>
#include <QSurfaceFormat>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),m_texture(nullptr),m_indexBuffer(QOpenGLBuffer::IndexBuffer)
    ,WKey(false),SKey(false),AKey(false),DKey(false),deltaTime(1.0f/60.0f)
{
    m_Camera = new Camera(QVector3D(0.0f,2.0f,8.0f));
    sphere1 = new SphereObj;
    sphere2 = new SphereObj;
    floor = new Floor;
    light = new Light;



    this->setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    sphere1->translate(QVector3D(-3.0f,5.0f,0.0f));
    sphere2->translate(QVector3D(3.0f,5.0f,0.0f));
    floor->translate(QVector3D(0.0f,-2.0f,0.0f));
    light->translate(QVector3D(0.0f,3.0f,-2.0f));

    sphere1->addForce(QVector3D(150.0f,10.0f,0.0f));
    sphere2->addForce(QVector3D(-150.0f,10.0f,0.0f));
    sphere2->addTorque(QVector3D(20.0f,0.0f,0.0f));

}

Widget::~Widget()
{
    delete m_Camera;
}

void Widget::initializeGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

   // QSurfaceFormat form;
   // form = format();
   // form.setSamples(16);
   // setFormat(form);

    initShaders();
    sphere1->init(1.0f);
    sphere2->init(1.0f);
    floor->init(50.0f,0.2f);
    light->init(0.5f,0.5f);
    objects.append(sphere1);
    objects.append(sphere2);
}

void Widget::resizeGL(int w, int h)
{
    float aspectRatio = w/float(h);
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45.0f,aspectRatio,0.1f,100.0f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("projectionMatrix", m_projectionMatrix);
    m_shaderProgram.setUniformValue("u_lightPosition", light->getPosition());
    m_shaderProgram.setUniformValue("blinn", 0.0f);
    moveCamera();


    qDebug()<<collisionDetector.sphereAndSphere(*sphere1,*sphere2);
    for(auto &obj : objects)
    {
        obj->move(deltaTime);
    }
    m_shaderLightProgram.bind();
    m_shaderLightProgram.setUniformValue("projectionMatrix", m_projectionMatrix);
    m_Camera->draw(&m_shaderLightProgram);
    light->draw(&m_shaderLightProgram,context()->functions());

    m_shaderProgram.bind();
    m_Camera->draw(&m_shaderProgram);
    sphere1->draw(&m_shaderProgram,context()->functions());
    sphere2->draw(&m_shaderProgram,context()->functions());
    floor->draw(&m_shaderProgram,context()->functions());
}

void Widget::initShaders()
{
    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,"C:\\Users\\Kostya\\Documents\\Kursachh\\vshader.vert"))
        close();
    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,"C:\\Users\\Kostya\\Documents\\Kursachh\\fshader.frag"))
        close();
    if(!m_shaderProgram.link())
        close();

    if(!m_shaderLightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,"C:\\Users\\Kostya\\Documents\\Kursachh\\light.vert"))
        close();
    if(!m_shaderLightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,"C:\\Users\\Kostya\\Documents\\Kursachh\\light.frag"))
        close();
    if(!m_shaderLightProgram.link())
        close();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
        m_previousMousePos = QVector2D(event->localPos());
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() != Qt::LeftButton)
        return;
    QVector2D diff = QVector2D(event->localPos()) - m_previousMousePos;
    m_previousMousePos = QVector2D(event->localPos());

    m_Camera->ProcessMouseMovement(diff.x(),diff.y());
    update();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    m_Camera->ProcessMouseScroll(event->delta());
    update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    handlePlayerInput(event->key(),true);
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    handlePlayerInput(event->key(),false);
}

void Widget::handlePlayerInput(int key, bool isPressed)
{
    if(key == 1062)
    {
       WKey = isPressed;
    }
    if(key == 1067)
    {
        SKey = isPressed;
    }
    if(key == 1060)
    {
        AKey = isPressed;
    }
    if(key == 1042)
    {
        DKey = isPressed;
    }
}

void Widget::moveCamera()
{
    if(WKey)
        m_Camera->ProcessKeyboard(Camera_Direction::Camera_Movement::FORWARD);
    if(SKey)
        m_Camera->ProcessKeyboard(Camera_Direction::Camera_Movement::BACKWARD);
    if(AKey)
        m_Camera->ProcessKeyboard(Camera_Direction::Camera_Movement::LEFT);
    if(DKey)
        m_Camera->ProcessKeyboard(Camera_Direction::Camera_Movement::RIGHT);
    update();
}
