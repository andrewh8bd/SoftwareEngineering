#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H
#include "event.h"

class CollisionEvent : public Event
{
  bool m_colliding;
  public:
  CollisionEvent();
  bool queryFor();
  void setColliding();
};

#endif
