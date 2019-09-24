#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "sphereobj.h"
#include "contact.h"


class CollisionDetector
{
public:
    QVector<Contact*> contacts;
    CollisionDetector();
    bool sphereAndSphere(const SphereObj &first,const SphereObj &second);
};

#endif // COLLISIONDETECTOR_H
