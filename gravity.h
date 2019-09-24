#ifndef GRAVITY_H
#define GRAVITY_H

#include<QVector3D>
#include<rigidbody.h>


class Gravity
{
public:
    Gravity(const QVector3D &m_gravity);
private:
    QVector3D gravity;
public:
    virtual void updateForce(RigidBody *body, float duration);
};

#endif // GRAVITY_H
