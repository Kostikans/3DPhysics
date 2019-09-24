#include "collisiondetector.h"


CollisionDetector::CollisionDetector()
{

}

bool CollisionDetector::sphereAndSphere(const SphereObj &first, const SphereObj &second)
{

    QVector3D firstPos = first.getPosition();
    QVector3D secondPos = second.getPosition();
    qDebug()<<firstPos;

    QVector3D delta = secondPos - firstPos;
    float distance = delta.length();
    if(distance <= 0.0f || distance >= first.getRadius() + second.getRadius())
        return false;

    QVector3D normal = delta  * (1.0f / distance);
    Contact *contact = new Contact;

    contact->contactNormal = normal;
    contact->contactPoint = firstPos + delta * 0.5f;
    contact->penetration = (first.getRadius() + second.getRadius() - distance);

    contact->body[0] = first.body;
    contact->body[1] = second.body;
    contacts.push_back(contact);
    return true;
}
