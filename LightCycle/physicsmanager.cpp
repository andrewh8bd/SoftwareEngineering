#include "physicsmanager.h"
#include "ogl-math/glm/gtc/type_ptr.hpp"
#include <gl/gl.h>

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
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glMultMatrixf(glm::value_ptr((*a)->getTransformation()));
    glBegin(GL_LINES);
      glVertex3f((*a)->getCorners()[0][0], 1.0, (*a)->getCorners()[0][1]);
      glVertex3f((*a)->getCorners()[1][0], 1.0, (*a)->getCorners()[1][1]);
      glVertex3f((*a)->getCorners()[1][0], 1.0, (*a)->getCorners()[1][1]);
      glVertex3f((*a)->getCorners()[2][0], 1.0, (*a)->getCorners()[2][1]);
      glVertex3f((*a)->getCorners()[2][0], 1.0, (*a)->getCorners()[2][1]);
      glVertex3f((*a)->getCorners()[3][0], 1.0, (*a)->getCorners()[3][1]);
      glVertex3f((*a)->getCorners()[3][0], 1.0, (*a)->getCorners()[3][1]);
      glVertex3f((*a)->getCorners()[0][0], 1.0, (*a)->getCorners()[0][1]);
    glEnd();
    glPopMatrix();
    for(std::vector<Box2D*>::iterator b = m_components.begin(); b != m_components.end(); b++)
    {
      if(*a != *b)
      {
        (*a)->intersect(**b);
      }
    }
  }
}

Box2D* PhysicsManager::createBox(const std::vector<glm::vec3>& vs)
{
  m_components.push_back(new Box2D(vs));
  return m_components.back();
}
