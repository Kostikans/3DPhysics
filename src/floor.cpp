#include "floor.h"
#include <QtMath>

Floor::Floor()
    :m_scale(1.0f), m_texture(nullptr),  m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}

void Floor::draw(QOpenGLShaderProgram *shaderProgram , QOpenGLFunctions *functions)
{
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(m_translate);
    modelMatrix.rotate(m_rotate);
    modelMatrix.scale(m_scale);

    m_arrayBuffer.bind();
    m_texture->bind(0);
    shaderProgram->setUniformValue("qt_Texture0", 0);
    int offset = 0;


    int vertloc = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertloc);
    shaderProgram->setAttributeBuffer(vertloc,GL_FLOAT,offset,3,sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texloc = shaderProgram->attributeLocation("a_texcoord");
    shaderProgram->enableAttributeArray(texloc);
    shaderProgram->setAttributeBuffer(texloc,GL_FLOAT,offset,2,sizeof(VertexData));


    offset += sizeof(QVector2D);

    int normloc = shaderProgram->attributeLocation("a_normal");
    shaderProgram->enableAttributeArray(normloc);
    shaderProgram->setAttributeBuffer(normloc,GL_FLOAT,offset,3,sizeof(VertexData));

    shaderProgram->setUniformValue("modelMatrix",modelMatrix);

    m_indexBuffer.bind();
    functions->glDrawElements(GL_TRIANGLES,m_indexBuffer.size(),GL_UNSIGNED_INT, nullptr);
    m_arrayBuffer.release();
    m_indexBuffer.release();
}

void Floor::translate(const QVector3D &translate)
{
    m_translate += translate;
}

void Floor::rotate(const QQuaternion &rotate)
{
    m_rotate = rotate * m_rotate;
}

void Floor::scale(const float &scale)
{
    m_scale *= scale;
}

void Floor::init(float m_width,float m_height)
{
    width = m_width/2.0f;
    height = m_height/2.0f;
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-width, height, width), QVector2D(0.0f, m_width), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-width, -height, width), QVector2D(0.0f, m_width), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(VertexData(QVector3D(width, height, width), QVector2D(m_width, m_width), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(VertexData(QVector3D(width, -height, width), QVector2D(m_width, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)));

    vertexes.append(VertexData(QVector3D(width, height, width), QVector2D(0.0f, m_width), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width, -height, width), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width, height, -width), QVector2D(m_width, m_width), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width, -height, -width), QVector2D(m_width, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)));

    vertexes.append(VertexData(QVector3D(width, height, width), QVector2D(0.0f, m_width), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width, height, -width), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width, height, width), QVector2D(m_width, m_width), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width, height, -width), QVector2D(m_width, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));

    vertexes.append(VertexData(QVector3D(width, height, -width), QVector2D(0.0f, m_width), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(VertexData(QVector3D(width, -height, -width), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(VertexData(QVector3D(-width, height, -width), QVector2D(m_width, m_width), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(VertexData(QVector3D(-width, -height, -width), QVector2D(m_width, 0.0f), QVector3D(0.0f, 0.0f, -1.0f)));

    vertexes.append(VertexData(QVector3D(-width, height, width), QVector2D(0.0f, m_width), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width, height, -width), QVector2D(0.0f, 0.0f), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width, -height, width), QVector2D(m_width, m_width), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width, -height, -width), QVector2D(m_width, 0.0f), QVector3D(-1.0f, 0.0f, 0.0f)));

    vertexes.append(VertexData(QVector3D(-width, -height, width), QVector2D(0.0f, m_width), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width, -height, -width), QVector2D(0.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width, -height, width), QVector2D(m_width, m_width), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width, -height, -width), QVector2D(m_width, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));

    QVector<GLuint> indexes;
    for (int i=0; i<24; i+=4){
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }
    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(),vertexes.size() * sizeof(VertexData));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(),indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();
    m_texture = new QOpenGLTexture(QImage("E:\\download\\parket2.0.jpg").mirrored());

    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

float Floor::getHeight() const
{
    return height;
}

float Floor::getWidth() const
{
    return width;
}

QVector3D Floor::getPosition() const
{
    return m_translate;
}
