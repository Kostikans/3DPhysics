#include "sphereobj.h"

#include <QtMath>

SphereObj::SphereObj()
    :m_scale(1.0f), m_texture(nullptr),  m_indexBuffer(QOpenGLBuffer::IndexBuffer),grav(QVector3D(0.0f,-9.81f,0.0f))
{
    body = new RigidBody;
    body->setMass(1.0f);
}

void SphereObj::draw(QOpenGLShaderProgram *shaderProgram , QOpenGLFunctions *functions)
{

    m_arrayBuffer.bind();
    m_texture->bind(0);
    shaderProgram->setUniformValue("qt_Texture0",0);
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

    shaderProgram->setUniformValue("modelMatrix",body->transformMatrix);

    m_indexBuffer.bind();
    functions->glDrawElements(GL_TRIANGLES,m_indexBuffer.size(),GL_UNSIGNED_INT, nullptr);
    m_arrayBuffer.release();
    m_indexBuffer.release();
}

void SphereObj::translate(const QVector3D &translate)
{
    body->setPosition(translate);
}

void SphereObj::rotate(const QQuaternion &rotate)
{
    m_rotate = rotate * m_rotate;
}

void SphereObj::scale(const float &scale)
{
    m_scale *= scale;
}

void SphereObj::init(float m_radius)
{
    radius = m_radius/2.0f;
    QVector<VertexData> vertexes;
    float sectorCount = 45;
    float stackCount = 45;
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            s = (float)j / sectorCount;
            t = (float)i / stackCount;

            vertexes.append(VertexData(QVector3D(x,y,z),QVector2D(s,t),QVector3D(nx,ny,nz)));
        }
    }
    QVector<GLuint> indices;
    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if(i != (stackCount-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(),vertexes.size() * sizeof(VertexData));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indices.constData(),indices.size() * sizeof(GLuint));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage("E:\\download\\TexturesCom_MetalBare0201_8_M.jpg"));

    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SphereObj::move(float deltaTime)
{
    grav.updateForce(body, deltaTime);
    body->integrate(deltaTime);
}

float SphereObj::getRadius() const
{
    return radius;
}

QVector3D SphereObj::getPosition() const
{
    return body->position;
}

void SphereObj::addForce(const QVector3D &force)
{
    body->addForce(force * body->getMass());
}

void SphereObj::addTorque(const QVector3D &torque)
{
    body->addTorque(torque * body->getMass());
}

