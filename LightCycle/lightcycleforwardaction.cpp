#include "lightcycleforwardaction.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include <iostream>

LightCycleForwardAction::LightCycleForwardAction() : m_cycle(NULL), m_velocity(glm::vec3(0.0, 0.0, 0.0)), m_running(false)
{
}

LightCycleForwardAction::LightCycleForwardAction(LightCycle* l = NULL, const glm::vec3& vel = glm::vec3(0.0, 0.0, 0.0)) : m_cycle(l), m_running(false), m_velocity(vel)
{
}

LightCycleForwardAction::~LightCycleForwardAction()
{                       
  m_cycle = NULL;
}

void LightCycleForwardAction::trigger()
{
  m_running = true;
  m_cycle->setVelocity(m_velocity);
}

bool LightCycleForwardAction::isRunning()
{
  return m_running;
}

bool LightCycleForwardAction::hasCompleted()
{
  return false;
}

//Depending on the addedtranslation based off of the change in time, the
//translation is updated.
void LightCycleForwardAction::update(float deltatime)
{
  glm::vec3 addedtranslation(0.0, 0.0, 0.0);
  glm::vec3 vel = m_cycle->getVelocity();
  glm::vec3 acc = m_cycle->getAcceleration();
  addedtranslation = vel * deltatime + acc * deltatime * deltatime * 0.5f;
  
  m_cycle->addTranslation(glm::vec3(addedtranslation[0], addedtranslation[1], addedtranslation[2]));
  
}
