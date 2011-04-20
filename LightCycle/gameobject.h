#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "ogl-math/glm/glm.hpp"

//This is the abstract base class that lets us use all kinds of game objects
//easily. It holds a rotation and a position for objects as well as
//several pure virtual functions to be overridden by it's children.
class GameObject
{
  protected:
  glm::vec3 m_rotation;
  glm::vec3 m_position;
  glm::vec3 m_scale;
  public:
  GameObject() : m_rotation(0.0, 0.0, 0.0), m_position(0.0, 0.0, 0.0) {}
  GameObject(const glm::vec3 p, const glm::vec3 r, const glm::vec3 s = glm::vec3(1.0, 1.0, 1.0)) : m_rotation(r), m_position(p), m_scale(s) {}
  virtual void setPosition(const glm::vec3&)=0;
  virtual glm::vec3 getPosition() const = 0;
  virtual void setRotation(const glm::vec3&)=0;
  virtual glm::vec3 getRotation() const = 0;
  virtual ~GameObject() {}
  virtual void update(const float)=0;
};

#endif
