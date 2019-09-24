#include "rigidbody.h"
#include <QtMath>

RigidBody::RigidBody()
{

}

void RigidBody::CalculateDerivedData()
{
    orientation.normalize();

    _calculateTransformMatrix(transformMatrix,position,orientation);
    _transformInertiaTensor(inverseInertiaTensorWorld, orientation,
                            inverseInertiaTensor,transformMatrix);
}

void RigidBody::_calculateTransformMatrix(QMatrix4x4 &transformMatrix, const QVector3D &position, const QQuaternion &orientation)
{
    transformMatrix.setToIdentity();
    transformMatrix.translate(position);
    transformMatrix.rotate(orientation);
}

void RigidBody::_transformInertiaTensor(QMatrix4x4 &iitWorld, const QQuaternion &q, const QMatrix3x3 &iitBody, const QMatrix4x4 &rotmat)
{
    float t4 = rotmat.data()[0]*iitBody.data()[0]+
    rotmat.data()[1]*iitBody.data()[3]+
    rotmat.data()[2]*iitBody.data()[6];

    float t9 = rotmat.data()[0]*iitBody.data()[1]+
    rotmat.data()[1]*iitBody.data()[4]+
    rotmat.data()[2]*iitBody.data()[7];

    float t14 = rotmat.data()[0]*iitBody.data()[2]+
    rotmat.data()[1]*iitBody.data()[5]+
    rotmat.data()[2]*iitBody.data()[8];

    float t28 = rotmat.data()[4]*iitBody.data()[0]+
    rotmat.data()[5]*iitBody.data()[3]+
    rotmat.data()[6]*iitBody.data()[6];

    float t33 = rotmat.data()[4]*iitBody.data()[1]+
    rotmat.data()[5]*iitBody.data()[4]+
    rotmat.data()[6]*iitBody.data()[7];

    float t38 = rotmat.data()[4]*iitBody.data()[2]+
    rotmat.data()[5]*iitBody.data()[5]+
    rotmat.data()[6]*iitBody.data()[8];

    float t52 = rotmat.data()[8]*iitBody.data()[0]+
    rotmat.data()[9]*iitBody.data()[3]+
    rotmat.data()[10]*iitBody.data()[6];

    float t57 = rotmat.data()[8]*iitBody.data()[1]+
    rotmat.data()[9]*iitBody.data()[4]+
    rotmat.data()[10]*iitBody.data()[7];

    float t62 = rotmat.data()[8]*iitBody.data()[2]+
    rotmat.data()[9]*iitBody.data()[5]+
    rotmat.data()[10]*iitBody.data()[8];

    iitWorld.data()[0] = t4*rotmat.data()[0]+
                       t9*rotmat.data()[1]+
                       t14*rotmat.data()[2];
    iitWorld.data()[1] = t4*rotmat.data()[4]+
                       t9*rotmat.data()[5]+
                       t14*rotmat.data()[6];
    iitWorld.data()[2] = t4*rotmat.data()[8]+
                       t9*rotmat.data()[9]+
                       t14*rotmat.data()[10];
    iitWorld.data()[3] = t28*rotmat.data()[0]+
                       t33*rotmat.data()[1]+
                       t38*rotmat.data()[2];
    iitWorld.data()[4] = t28*rotmat.data()[4]+
                       t33*rotmat.data()[5]+
                       t38*rotmat.data()[6];
    iitWorld.data()[5] = t28*rotmat.data()[8]+
                       t33*rotmat.data()[9]+
                       t38*rotmat.data()[10];
    iitWorld.data()[6] = t52*rotmat.data()[0]+
                       t57*rotmat.data()[1]+
                       t62*rotmat.data()[2];
    iitWorld.data()[7] = t52*rotmat.data()[4]+
                       t57*rotmat.data()[5]+
                       t62*rotmat.data()[6];
    iitWorld.data()[8] = t52*rotmat.data()[8]+
                       t57*rotmat.data()[9]+
                       t62*rotmat.data()[10];
}

void RigidBody::setInertiaTensor(const QMatrix3x3 &inertiaTensor)
{
    inverseInertiaTensor = inertiaTensor.transposed();
}

void RigidBody::addForce(const QVector3D &force)
{
    forceAccum += force;
}

float RigidBody::getMass() const
{
    return 1.0f/inverseMass;
}

void RigidBody::integrate(float duration)
{
    lastFrameAcceleration = acceleration;
    lastFrameAcceleration += forceAccum * inverseMass;

    QVector3D angularAcceleration = inverseInertiaTensorWorld * torqueAccum;


    velocity += lastFrameAcceleration * duration;
    rotation += angularAcceleration * duration;

    //velocity *= pow(linearDamping, duration);
    //rotation *= pow(angularDamping, duration);

    position += velocity * duration;


    QQuaternion temp;
    temp.setScalar(0.0f);
    temp.setVector(rotation * duration);
    temp *= orientation;
    orientation += temp;

    //velocity *= pow(linearDamping, duration);
    // rotation *= pow(angularDamping, duration);

    CalculateDerivedData();
    clearAccumulators();
}

void RigidBody::clearAccumulators()
{
    forceAccum = QVector3D(0.0f,0.0f,0.0f);
    torqueAccum = QVector3D(0.0f,0.0f,0.0f);
}

void RigidBody::setVelocity(const QVector3D &m_velocity)
{
    velocity = m_velocity;
}

void RigidBody::setPosition(const QVector3D &m_position)
{
    position = m_position;
}

void RigidBody::setMass(const float &mass)
{
    inverseMass = 1.0f/mass;
}

void RigidBody::addForceAtPoint(const QVector3D &force, const QVector3D &point)
{
    QVector3D pt = point;
    pt -= position;

    forceAccum += force;
    torqueAccum += QVector3D::crossProduct(pt, force);
}

void RigidBody::addTorque(const QVector3D &torque)
{
    torqueAccum += torque;
}

void RigidBody::addVelocity(const QVector3D &m_velocity)
{
    velocity += m_velocity;
}

void RigidBody::addRotation(const QVector3D &m_rotation)
{
    rotation += m_rotation;
}

QVector3D RigidBody::getLastFrameAcceleration() const
{
    return lastFrameAcceleration;
}

QVector3D RigidBody::getRotation() const
{
    return rotation;
}

QVector3D RigidBody::getPosition() const
{
    return position;
}

QVector3D RigidBody::getVelocity() const
{
    return velocity;
}
