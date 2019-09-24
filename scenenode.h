#ifndef SCENENODE_H
#define SCENENODE_H

#include <iostream>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

struct VertexData
{
    VertexData();
    VertexData(QVector3D m_pos,QVector2D m_texCoord,QVector3D m_norm)
    {
        position = m_pos;
        texCoord = m_texCoord;
        normal = m_norm;
    }
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

class SceneNode
{
public:
    SceneNode();
private:


};

#endif // SCENENODE_H
