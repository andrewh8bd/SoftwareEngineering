#include "lightcycle.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include <iostream>

LightCycle::LightCycle(GraphicsComponent* g, glm::vec4 color)
  : m_graphicscomponent(g), m_color(color), m_velocity(glm::vec3(0.0, 0.0, 0.0)),
    m_acceleration(glm::vec3(0.0, 0.0, 0.0)), m_angularvelocity(glm::vec3(0.0, 0.0, 0.0)),
    m_angularacceleration(glm::vec3(0.0, 0.0, 0.0)), 
    GameObject(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0)), m_turntime(0.25), m_timetaken(0.0)
{
}

LightCycle::~LightCycle()
{
  delete m_graphicscomponent;
}

void LightCycle::setColor(const glm::vec4& v)
{
  m_color = v;
}

glm::vec4 LightCycle::getColor() const
{
  return m_color;
}

void LightCycle::setPosition(const glm::vec3& v)
{
  m_position = v;
}

void LightCycle::addTranslation(const glm::vec3& v)
{
  m_position += v;
}

glm::vec3 LightCycle::getPosition() const
{
  return m_position;
}

void LightCycle::setRotation(const glm::vec3& v)
{
  m_rotation = v;
}

void LightCycle::addRotation(const glm::vec3& v)
{
  m_rotation += v;
}

glm::vec3 LightCycle::getRotation() const
{
  return m_rotation;
}

void LightCycle::setVelocity(const glm::vec3& v)
{
  m_velocity = v;
}

glm::vec3 LightCycle::getVelocity() const
{
  return m_velocity;
}

void LightCycle::setAcceleration(const glm::vec3& v)
{
  m_acceleration = v;
}

glm::vec3 LightCycle::getAcceleration() const
{
  return m_acceleration;
}

glm::vec3 LightCycle::getAngularVelocity() const
{
  return m_angularvelocity;
}

void LightCycle::setAngularVelocity(const glm::vec3& v)
{
  m_angularvelocity = v;
}

glm::vec3 LightCycle::getAngularAcceleration() const
{
  return m_angularacceleration;
}

void LightCycle::setAngularAcceleration(const glm::vec3& v)
{
  m_angularacceleration = v;
}

void LightCycle::setTransformation(const glm::mat4& m )
{
  m_graphicscomponent->setTransformation(m);
}

glm::mat4 LightCycle::getTransformation()
{
  return m_graphicscomponent->getTransformation();
}

void LightCycle::update(const float deltatime)
{
  glm::mat4 newtrans(1.0);
  
  newtrans = glm::translate(newtrans, m_position);
  newtrans = glm::rotate(newtrans, m_rotation[0], glm::vec3(1.0, 0.0, 0.0));
  newtrans = glm::rotate(newtrans, m_rotation[1], glm::vec3(0.0, 1.0, 0.0));
  newtrans = glm::rotate(newtrans, m_rotation[2], glm::vec3(0.0, 0.0, 1.0));
  
  
  m_graphicscomponent->setTransformation(newtrans);
}
