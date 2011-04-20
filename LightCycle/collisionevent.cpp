#include "collisionevent.h"

CollisionEvent::CollisionEvent() : m_colliding(false)
{
}

bool CollisionEvent::queryFor()
{
  return m_colliding;
}

void CollisionEvent::setColliding()
{
  m_colliding = true;
}
