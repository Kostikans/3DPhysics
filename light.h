#ifndef LIGHT_H
#define LIGHT_H

#include "scenenode.h"

class Light : public SceneNode
{
public:
    Light();
    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions);
    void translate(const QVector3D &translate);
    void rotate(const QQuaternion &rotate);
    void scale(const float &scale);
    void init(float m_width,float m_height);

    float getHeight() const;
    float getWidth() const;
    QVector3D getPosition() const;

private:
    QMatrix4x4 modelMatrix;
    QQuaternion m_rotate;
    QVector3D m_translate;
    float m_scale;
    float height,width;

    QOpenGLTexture *m_texture;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLBuffer m_arrayBuffer;


};


#endif // LIGHT_H
