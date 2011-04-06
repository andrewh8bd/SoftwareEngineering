#include "lightcycleaccelerateaction.h"
#include <iostream>
#include <cmath>

LightCycleAccelerateAction::LightCycleAccelerateAction() : m_cycle(NULL), m_acceleration(glm::vec3(0.0, 0.0, 0.0))
{
  m_running = false;
}

LightCycleAccelerateAction::LightCycleAccelerateAction(LightCycle* l = NULL, const glm::vec3& acc = glm::vec3(0.0, 0.0, 0.0), const bool absolute = true) : m_cycle(l), m_acceleration(acc), m_isabsolute(absolute)
{
  m_running = false;
}

LightCycleAccelerateAction::~LightCycleAccelerateAction()
{                       
  m_cycle = NULL;
}

void LightCycleAccelerateAction::trigger()
{
  m_running = true;
  m_startvelocity = m_cycle->getBaseVelocity();
  glm::vec4 rotatedaccel = glm::rotate(glm::mat4(1.0), m_cycle->getRotation()[1],
                                glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_acceleration, 1.0);
  m_cycle->setAcceleration(glm::vec3(rotatedaccel[0], rotatedaccel[1], rotatedaccel[2]));
}

bool LightCycleAccelerateAction::isRunning()
{
  return m_running;
}

bool LightCycleAccelerateAction::hasCompleted()
{
  if(m_isabsolute)
  {
    m_running = false;
    return true;
  }
  else
  {
    if(fabs(glm::length(m_cycle->getVelocity()) - glm::length(m_cycle->getBaseVelocity())) < 0.01)
    {
      m_running = false;
      m_cycle->setAcceleration(glm::vec3(0.0, 0.0, 0.0));
      glm::vec4 rotatedvel = glm::rotate(glm::mat4(1.0), m_cycle->getRotation()[1],
                                glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_cycle->getBaseVelocity(), 1.0);
      m_cycle->setVelocity(glm::vec3(rotatedvel[0], rotatedvel[1], rotatedvel[2]));
      return true;
    }
    else
      return false;
  }
}

//Depending on the addedtranslation based off of the change in time, the
//translation is updated.
void LightCycleAccelerateAction::update(float deltatime)
{
}
