#include "lightcycle.h"
#include "physicsmanager.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/type_ptr.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include "renderer.h"
#include <iostream>
#include <vector>

LightCycle::LightCycle(GraphicsComponent* g, Box2D* box, const glm::vec3& pos, const glm::vec3& rot, const glm::vec4& color)
  : m_graphicscomponent(g), m_color(color), m_velocity(glm::vec3(0.0, 0.0, 0.0)),
    m_acceleration(glm::vec3(0.0, 0.0, 0.0)), m_angularvelocity(glm::vec3(0.0, 0.0, 0.0)),
    m_angularacceleration(glm::vec3(0.0, 0.0, 0.0)), 
    GameObject(pos, rot), m_boundingbox(box)
{
}

LightCycle::~LightCycle()
{
  delete m_graphicscomponent;
  delete m_boundingbox;
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
  m_walls.back()->setEndPoint(m_position);
}

void LightCycle::addTranslation(const glm::vec3& v)
{
  m_position += v;
  m_walls.back()->setEndPoint(m_position);
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
  m_boundingbox->setTransformation(m);
}

glm::mat4 LightCycle::getTransformation()
{
  return m_graphicscomponent->getTransformation();
}

void LightCycle::addNewWall()
{
  std::vector<glm::vec3> wallverts;
  std::vector<glm::vec3> wallnorms;
  std::vector<glm::vec2> walltexs;
  
  wallverts.push_back(glm::vec3(m_position[0], 0.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 0.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 1.0, m_position[2]));
  
  wallverts.push_back(glm::vec3(m_position[0], 1.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 0.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 0.0, m_position[2]));
  
  wallverts.push_back(glm::vec3(m_position[0], 1.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 1.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 0.0, m_position[2]));
      
  wallverts.push_back(glm::vec3(m_position[0], 0.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 1.0, m_position[2]));
  wallverts.push_back(glm::vec3(m_position[0], 1.0, m_position[2]));
  
  glm::vec3 newposnorm = glm::normalize(glm::cross(wallverts[1] - wallverts[0], wallverts[2] - wallverts[0]));
  glm::vec3 newnegnorm = glm::normalize(glm::cross(wallverts[4] - wallverts[3], wallverts[5] - wallverts[3]));
    
  wallnorms.push_back(newposnorm);
  wallnorms.push_back(newposnorm);
  wallnorms.push_back(newposnorm);
  
  wallnorms.push_back(newnegnorm);
  wallnorms.push_back(newnegnorm);
  wallnorms.push_back(newnegnorm);
  
  wallnorms.push_back(newposnorm);
  wallnorms.push_back(newposnorm);
  wallnorms.push_back(newposnorm);
      
  wallnorms.push_back(newnegnorm);
  wallnorms.push_back(newnegnorm);
  wallnorms.push_back(newnegnorm);
  
  walltexs.push_back(glm::vec2(0.0, 0.0));
  walltexs.push_back(glm::vec2(0.0, 1.0));
  walltexs.push_back(glm::vec2(1.0, 1.0));
  
  walltexs.push_back(glm::vec2(1.0, 1.0));
  walltexs.push_back(glm::vec2(0.0, 1.0));
  walltexs.push_back(glm::vec2(0.0, 0.0));
  
  walltexs.push_back(glm::vec2(1.0, 1.0));
  walltexs.push_back(glm::vec2(1.0, 0.0));
  walltexs.push_back(glm::vec2(0.0, 0.0));
      
  walltexs.push_back(glm::vec2(0.0, 0.0));
  walltexs.push_back(glm::vec2(1.0, 0.0));
  walltexs.push_back(glm::vec2(1.0, 1.0));
  GraphicsComponent* newgp = Renderer::getInstance()->createDynamicGraphicsComponent(wallverts, wallnorms, walltexs);
  Box2D* newbox = PhysicsManager::getInstance()->createBox(glm::vec2(m_position[0], m_position[2]),
                                                           glm::vec2(m_position[0], m_position[2]));
  LightCycleWall* newwall = new LightCycleWall(newgp, newbox, m_color);
  m_walls.push_back(newwall);
}

void LightCycle::update(const float deltatime)
{
  glm::mat4 newtrans(1.0);
  
  newtrans = glm::translate(newtrans, m_position);
  newtrans = glm::rotate(newtrans, m_rotation[0], glm::vec3(1.0, 0.0, 0.0));
  newtrans = glm::rotate(newtrans, m_rotation[1], glm::vec3(0.0, 1.0, 0.0));
  newtrans = glm::rotate(newtrans, m_rotation[2], glm::vec3(0.0, 0.0, 1.0));
  
  
  m_graphicscomponent->setTransformation(newtrans);
  m_boundingbox->setTransformation(newtrans);
  static glm::vec3 color(1.0, 0.0, 1.0);
  for(std::vector<Box2D*>::iterator it = m_boundingbox->getColliders().begin();
      it != m_boundingbox->getColliders().end(); it++)
  {
    if(*it != m_walls.back()->getBoundingBox() && (m_walls.size() >= 2 && m_walls[m_walls.size() - 2]->getBoundingBox() != (*it)))
    {
      color[0] *= -1.0; color[0] += 1.0;
      color[1] *= -1.0; color[1] += 1.0;
      color[2] *= -1.0; color[2] += 1.0;
    }
  }
  glColor3fv(glm::value_ptr(color));
  m_boundingbox->clearColliders();
  
}

void LightCycle::setBaseVelocity(const glm::vec3& v)
{
  m_startingvelocity = v;
}

glm::vec3 LightCycle::getBaseVelocity() const
{
  return m_startingvelocity;
}
