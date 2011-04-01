#ifndef LIGHTCYCLEWALL_H
#define LIGHTCYCLEWALL_H
#include "gameobject.h"
#include "graphicscomponent.h"
#include "ogl-math/glm/glm.hpp"

class LightCycleWall 
{
  private:
  GraphicsComponent* m_graphicscomponent;
  glm::vec4 m_color;
  public:
  LightCycleWall();
  LightCycleWall(GraphicsComponent* g, const glm::vec4&);
  void setEndPoint(const glm::vec3&);
};

#endif
