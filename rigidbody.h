#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QMatrix3x3>

class RigidBody
{
public:
    RigidBody();

    float inverseMass;
    float angularDamping;
    float linearDamping;
    QQuaternion orientation;

    QVector3D position;
    QVector3D velocity;
    QVector3D rotation;

    QVector3D forceAccum;
    QVector3D torqueAccum;

    QVector3D acceleration;
    QVector3D lastFrameAcceleration;

    QMatrix3x3 inverseInertiaTensor;
    QMatrix4x4 inverseInertiaTensorWorld;
    QMatrix4x4 transformMatrix;
private:

    static inline void _calculateTransformMatrix(QMatrix4x4 &transformMatrix,
                                                 const QVector3D &position,
                                                 const QQuaternion &orientation);
    static inline void _transformInertiaTensor(QMatrix4x4 &iitWorld,
                                               const QQuaternion &q,
                                               const QMatrix3x3 &iitBody,
                                               const QMatrix4x4 &rotmat);
    void CalculateDerivedData();
public:

    void setInertiaTensor(const QMatrix3x3  &inertiaTensor);
    void addForce(const QVector3D &force);
    float getMass() const;
    void integrate(float duration);
    void clearAccumulators();
    void setVelocity(const QVector3D &m_velocity);
    void setPosition(const QVector3D &m_position);
    void setMass(const float &mass);
    void addForceAtPoint(const QVector3D &force, const QVector3D &point);
    void addTorque(const QVector3D &torque);
    void addVelocity(const QVector3D &m_velocity);
    void addRotation(const QVector3D &m_rotation);
    QVector3D getLastFrameAcceleration() const;
    QVector3D getRotation() const;
    QVector3D getPosition() const;
    QVector3D getVelocity() const;
};

#endif // RIGIDBODY_H
