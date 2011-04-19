#include "turnlightcycleaction.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include <iostream>

TurnLightCycleAction::TurnLightCycleAction(LightCycle* c, const DIRECTION d, const float tt) : m_cycle(c), m_direction(d), m_timetaken(0.0), m_turntime(tt), m_running(false)
{
}
TurnLightCycleAction::~TurnLightCycleAction()
{
  m_cycle = NULL;
}

void TurnLightCycleAction::trigger()
{
  if(!m_cycle->getAlreadyTurning())
  {
    m_running = true;
    if(m_direction == RIGHT)
      m_cycle->setAngularVelocity(glm::vec3(0.0, 90.0 / m_turntime, 0.0));
    if(m_direction == LEFT)
      m_cycle->setAngularVelocity(glm::vec3(0.0, 90.0 / -m_turntime, 0.0));
    m_oldvelocity = m_cycle->getVelocity();
    m_oldrotation = m_cycle->getRotation();
    m_oldacceleration = m_cycle->getAcceleration();
    m_cycle->setVelocity(glm::vec3(0.0, 0.0, 0.0));
    m_cycle->setAcceleration(glm::vec3(0.0, 0.0, 0.0));
    m_cycle->setAlreadyTurning(true);
  }
}

bool TurnLightCycleAction::isRunning()
{
  return m_running;
}

//Based on that angular velocity, add a rotation to dat shit.
void TurnLightCycleAction::update(float deltatime)
{
  glm::vec3 addedrotation(0.0, 0.0, 0.0);
  
  if(m_timetaken + deltatime > m_turntime)
  {
    deltatime = (m_turntime - m_timetaken);
    m_timetaken = m_turntime;
  }
  else
  {
    m_timetaken += deltatime;
  }
  
  glm::vec3 angvel = m_cycle->getAngularVelocity();
  glm::vec3 angacc = m_cycle->getAngularAcceleration();
  
  addedrotation = angvel * deltatime + angacc * deltatime * deltatime * 0.5f;
  
  m_cycle->addRotation(addedrotation);
  
}

//This is neat. Makes sense to me.
bool TurnLightCycleAction::hasCompleted()
{
  if(m_timetaken >= m_turntime && m_running)
  {
    m_running = false;
    m_timetaken = 0.0;
    m_cycle->setAngularVelocity(glm::vec3(0.0, 0.0, 0.0));
  
    glm::vec4 rotatedvelocity = glm::rotate(glm::mat4(1.0), m_cycle->getRotation()[1] - m_oldrotation[1],
                                  glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_oldvelocity, 1.0);
    
    glm::vec4 rotatedaccel = glm::rotate(glm::mat4(1.0), m_cycle->getRotation()[1] - m_oldrotation[1],
                                  glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_oldacceleration, 1.0);
    m_cycle->setVelocity(glm::vec3(rotatedvelocity[0], rotatedvelocity[1], rotatedvelocity[2]));
    m_cycle->setAcceleration(glm::vec3(rotatedaccel[0], rotatedaccel[1], rotatedaccel[2]));
    m_cycle->addNewWall();
    m_cycle->setAlreadyTurning(false);
    return true;
  }
  return false;
}
