#include "gravity.h"

Gravity::Gravity(const QVector3D &m_gravity)
{
    gravity = m_gravity;
}

void Gravity::updateForce(RigidBody *body, float duration)
{
   // if (!body->hasFiniteMass()) return;
    body->addForce(gravity * body->getMass());
}
