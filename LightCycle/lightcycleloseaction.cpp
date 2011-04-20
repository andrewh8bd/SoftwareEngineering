#include "lightcycleloseaction.h"
#include <iostream>
LightCycleLoseAction::LightCycleLoseAction() : m_cycle(NULL), m_time(1.0), m_camera(NULL), m_running(false), m_elapsedtime(0.0), m_cameravelocity(0.0, 0.0, 0.0)
{
}

LightCycleLoseAction::LightCycleLoseAction(LightCycle* l, Camera* c, const float time)
 : m_cycle(l), m_camera(c), m_time(time), m_running(false), m_elapsedtime(0.0), m_cameravelocity(0.0, 0.0, 0.0)
{
}

LightCycleLoseAction::~LightCycleLoseAction()
{
  m_cycle = NULL;
  m_camera = NULL;
}

void LightCycleLoseAction::trigger()
{
  m_cameravelocity = -1.0f * m_camera->getVelocity() + glm::vec3(0.0, 5.0, 0.0);
  m_cycle->setVelocity(glm::vec3(0.0, 0.0, 0.0));
  m_cycle->setAcceleration(glm::vec3(0.0, 0.0, 0.0));
  m_cycle->setAlreadyTurning(true);
  m_camera->setVelocity(m_cameravelocity);
  m_camera->setAngularVelocity(glm::vec3(30.0, 0.0, 0.0));
  m_camera->setAcceleration(glm::vec3(0.0, 0.0, 0.0));
  m_camera->setAlreadyTurning(true);
  m_running = true;
  m_elapsedtime = 0.0;
}

bool LightCycleLoseAction::isRunning()
{
  return m_running;
}

bool LightCycleLoseAction::hasCompleted()
{
  if(m_elapsedtime >= m_time && m_running)
  {
    m_camera->setVelocity(glm::vec3(0.0, 0.0, 0.0));
    m_camera->setAngularVelocity(glm::vec3(0.0, 0.0, 0.0));
    return true;
  }
  return false;
}

void LightCycleLoseAction::update(float deltatime)
{
  if(m_elapsedtime + deltatime > m_time)
  {
    deltatime = (m_time - m_elapsedtime);
    m_elapsedtime = m_time;
  }
  else
  {
    m_elapsedtime += deltatime;
  }
  glm::vec3 addedrotation(0.0, 0.0, 0.0);
  m_cycle->setScale(m_cycle->getScale() - ((deltatime / m_time) * glm::vec3(0.0, 1.0, 0.0)));
  
  glm::vec3 angvel = m_cycle->getAngularVelocity();
  glm::vec3 angacc = m_cycle->getAngularAcceleration();
  
  addedrotation = angvel * deltatime + angacc * deltatime * deltatime * 0.5f;
  
  m_cycle->addRotation(addedrotation);
}
