#ifndef LIGHTCYCLEWALL_H
#define LIGHTCYCLEWALL_H
#include "gameobject.h"
#include "graphicscomponent.h"
#include "box2d.h"
#include "ogl-math/glm/glm.hpp"

class LightCycleWall 
{
  private:
  GraphicsComponent* m_graphicscomponent;
  Box2D* m_boundingbox;
  glm::vec4 m_color;
  public:
  LightCycleWall();
  LightCycleWall(GraphicsComponent* g, Box2D* box, const glm::vec4&);
  void setEndPoint(const glm::vec3&);
  Box2D* getBoundingBox() const;
  void setColor(const glm::vec4&);
};

#endif
