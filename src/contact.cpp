#include "contact.h"
#include <QtMath>

Contact::Contact()
{

}

void Contact::setContactData(RigidBody *first, RigidBody *second)
{
    body[0] = first;
    body[1] = second;
}

void Contact::calculateContactBasis()
{
    QVector3D contactTangent[2];
    if(abs(contactNormal.x()) > abs(contactNormal.y()))
    {
        const float z = 1.0f/ sqrt(contactNormal.z() * contactNormal.z() +
                                   contactNormal.x() * contactNormal.x());

        contactTangent[0].setX(contactNormal.z() * z);
        contactTangent[0].setY(0);
        contactTangent[0].setZ(-contactNormal.x() * z);

        contactTangent[1].setX(contactNormal.y() * contactTangent[0].x());
        contactTangent[1].setY(contactNormal.z() * contactTangent[0].x() -
                              contactNormal.x() *contactTangent[0].z());
        contactTangent[1].setZ(-contactNormal.y() *contactTangent[0].x());
    }
    else {
        const float z = 1.0f/ sqrt(contactNormal.z() * contactNormal.z() +
                                   contactNormal.y() * contactNormal.y());

        contactTangent[0].setX(0);
        contactTangent[0].setY(-contactNormal.z() * z);
        contactTangent[0].setZ( contactNormal.y() * z);

        contactTangent[1].setX(- contactNormal.y() * contactTangent[0].z()-
                               contactNormal.z() * contactTangent[0].y());
        contactTangent[1].setY(-contactNormal.x() * contactTangent[0].z());
        contactTangent[1].setZ( contactNormal.x() *contactTangent[0].y());
    }
    contactToWorld.data()[0] = contactNormal.x();
    contactToWorld.data()[1] = contactNormal.y();
    contactToWorld.data()[2] = contactNormal.y();

    contactToWorld.data()[3] = contactTangent[0].x();
    contactToWorld.data()[4] = contactTangent[0].y();
    contactToWorld.data()[5] = contactTangent[0].z();

    contactToWorld.data()[6] = contactTangent[1].x();
    contactToWorld.data()[7] = contactTangent[1].y();
    contactToWorld.data()[8] = contactTangent[1].z();
}

QVector3D Contact::calculateLocalVelocity(unsigned int bodyIndex, float duration)
{
    RigidBody *thisBody = body[bodyIndex];


        QVector3D velocity =
            QVector3D::crossProduct(thisBody->getRotation(), relativeContactPosition[bodyIndex]);
        velocity += thisBody->getVelocity();


        QVector3D contactVelocity = transformTranspose(contactToWorld,velocity);

        QVector3D accVelocity = thisBody->getLastFrameAcceleration() * duration;


        accVelocity = transformTranspose(contactToWorld,accVelocity);


        accVelocity.setX(0);


        contactVelocity += accVelocity;

        return contactVelocity;
}

void Contact::calculateInternals(float duration)
{
    calculateContactBasis();
    relativeContactPosition[0] = contactPoint - body[0]->getPosition();
    relativeContactPosition[1] = contactPoint - body[1]->getPosition();
    contactVelocity = calculateLocalVelocity(0, duration);
  //  contactVelocity -= calculateLocalVelocity(1, duration);
}

void Contact::calculateDesiredDeltaVelocity(float duration)
{
    const static float  velocityLimit = 0.25f;

    // Calculate the acceleration induced velocity accumulated this frame
    float velocityFromAcc = 0;
    velocityFromAcc += body[0]->getLastFrameAcceleration().length() * duration * contactNormal.length();
    // If the velocity is very slow, limit the restitution
    velocityFromAcc -= body[1]->getLastFrameAcceleration().length() * duration * contactNormal.length();

    // Combine the bounce velocity with the removed
    // acceleration velocity.
    desiredDeltaVelocity = -contactVelocity;
}

void Contact::calculateImpulse(QMatrix3x3 *inversInertiaTensor)
{
    QVector3D impulseContact;
    float inverseMass = body[0]->getMass();

}

void Contact::adjustVelocities(Contact *c, float duration)
{
   //QVector3D velocityChange = impulse * body[0]->getInverseMass();
}

void Contact::adjustPositions(Contact *c, float duration)
{

}
QVector3D Contact::transformTranspose(const QMatrix3x3 &matrix, const QVector3D &vector)
{
    return QVector3D(
                   vector.x() * matrix.data()[0] + vector.y() * matrix.data()[3] + vector.z() * matrix.data()[6],
                   vector.x() * matrix.data()[1] + vector.y() * matrix.data()[4] + vector.z() * matrix.data()[7],
                   vector.x() * matrix.data()[2] + vector.y() * matrix.data()[5] + vector.z() * matrix.data()[8]
               );
}
