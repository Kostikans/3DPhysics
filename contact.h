#ifndef CONTACT_H
#define CONTACT_H

#include "rigidbody.h"



class Contact
{
public:
    Contact();
    void setContactData(RigidBody *first, RigidBody *second);
    void calculateContactBasis();
    QVector3D calculateLocalVelocity(unsigned int bodyIndex,float duration);
    void calculateInternals(float duration);
    void calculateDesiredDeltaVelocity(float duration);
    void calculateImpulse(QMatrix3x3 *inversInertiaTensor);
    void adjustVelocities(Contact *c,float duration);
    void adjustPositions(Contact *c,float duration);


    RigidBody* body[2];
    QVector3D contactVelocity;
    QVector3D contactPoint;
    QVector3D contactNormal;
    QVector3D relativeContactPosition[2];
    QVector3D desiredDeltaVelocity;
    float penetration;
    QMatrix3x3 contactToWorld;

    QVector3D transformTranspose(const QMatrix3x3 &matrix,const QVector3D &vector);


};

#endif // CONTACT_H
