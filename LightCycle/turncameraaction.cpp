#include "turncameraaction.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include <iostream>

bool TurnCameraAction::m_alreadyturning = false;

TurnCameraAction::TurnCameraAction(Camera* c, const DIRECTION d, const float tt) : m_camera(c), m_direction(d), m_timetaken(0.0), m_turntime(tt), m_running(false)
{
}

TurnCameraAction::~TurnCameraAction()
{
  m_camera = NULL;
}

void TurnCameraAction::trigger()
{
  if(!m_alreadyturning)
  {
    m_running = true;
    if(m_direction == RIGHT)
      m_camera->setAngularVelocity(glm::vec3(0.0, 90.0 / m_turntime, 0.0));
    if(m_direction == LEFT)
      m_camera->setAngularVelocity(glm::vec3(0.0, 90.0 / -m_turntime, 0.0));
    m_oldvelocity = m_camera->getVelocity();
    m_oldrotation = m_camera->getRotation();
    m_oldacceleration = m_camera->getAcceleration();
    m_camera->setVelocity(glm::vec3(0.0, 0.0, 0.0));
    m_camera->setAcceleration(glm::vec3(0.0, 0.0, 0.0));
    m_alreadyturning = true;
  }
}

bool TurnCameraAction::isRunning()
{
  return m_running;
}

void TurnCameraAction::update(float deltatime)
{
  glm::vec3 addedrotation(0.0, 0.0, 0.0);
  if(m_timetaken + deltatime > m_turntime)
  {
    deltatime = m_turntime - m_timetaken;
    m_timetaken = m_turntime;
  }
  else
  {
    m_timetaken += deltatime;
  }
  
  glm::vec3 angvel = m_camera->getAngularVelocity();
  glm::vec3 angacc = m_camera->getAngularAcceleration();
  
  addedrotation = angvel * deltatime + angacc * deltatime * deltatime * 0.5f;
  
  m_camera->setRotation(addedrotation + m_camera->getRotation());
}

bool TurnCameraAction::hasCompleted()
{
  if(m_timetaken >= m_turntime && m_running)
  {
    m_running = false;
    m_timetaken = 0.0;
    m_camera->setAngularVelocity(glm::vec3(0.0, 0.0, 0.0));
    
    glm::vec4 rotatedvelocity = glm::rotate(glm::mat4(1.0), m_camera->getRotation()[1] - m_oldrotation[1],
                                  glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_oldvelocity, 1.0);
    
    glm::vec4 rotatedaccel = glm::rotate(glm::mat4(1.0), m_camera->getRotation()[1] - m_oldrotation[1],
                                  glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_oldacceleration, 1.0);
    m_camera->setAcceleration(glm::vec3(rotatedaccel[0], rotatedaccel[1], rotatedaccel[2]));    
    m_camera->setVelocity(glm::vec3(rotatedvelocity[0], rotatedvelocity[1], rotatedvelocity[2]));
    m_alreadyturning = false;
    return true;
  }
  return false;
}
