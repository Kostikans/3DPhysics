#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "rigidbody.h"
#include "QMatrix4x4"

class Primitive
{
public:
    Primitive();
    RigidBody *body;
    QMatrix4x4 offset;
};

#endif // PRIMITIVE_H
