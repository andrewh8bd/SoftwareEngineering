#include "physicsmanager.h"
#include "ogl-math/glm/gtc/type_ptr.hpp"
#include <gl/gl.h>
#include <iostream>

PhysicsManager* PhysicsManager::m_instance = NULL;

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

PhysicsManager* PhysicsManager::getInstance()
{
  if(m_instance == NULL)
    m_instance = new PhysicsManager;
  return m_instance;
}

void PhysicsManager::dump()
{
  for(std::vector<Box2D*>::iterator it = m_components.begin(); it != m_components.end(); it++)
  {
    delete (*it);
  }
  m_components.clear();
  delete m_instance;
}

void PhysicsManager::update()
{
  for(std::vector<Box2D*>::iterator a = m_components.begin(); a != m_components.end(); a++)
  {
    for(std::vector<Box2D*>::iterator b = m_components.begin(); b != m_components.end(); b++)
    {
      if(*a != *b)
      {
        (*a)->intersect(*b);
      }
    }
  }
}

Box2D* PhysicsManager::createBox(const std::vector<glm::vec3>& vs)
{
  m_components.push_back(new Box2D(vs));
  return m_components.back();
}

Box2D* PhysicsManager::createBox(const glm::vec2& a, const glm::vec2& b)
{
  m_components.push_back(new Box2D(a, b));
  return m_components.back();
}
