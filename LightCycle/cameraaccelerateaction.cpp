#include "cameraaccelerateaction.h"
#include "Cameraaccelerateaction.h"
#include <iostream>
#include <cmath>

CameraAccelerateAction::CameraAccelerateAction() : m_camera(NULL), m_acceleration(glm::vec3(0.0, 0.0, 0.0))
{
  m_running = false;
}

CameraAccelerateAction::CameraAccelerateAction(Camera* l = NULL, const glm::vec3& acc = glm::vec3(0.0, 0.0, 0.0), const bool absolute = true) : m_camera(l), m_acceleration(acc), m_isabsolute(absolute)
{
  m_running = false;
}

CameraAccelerateAction::~CameraAccelerateAction()
{                       
  m_camera = NULL;
}

void CameraAccelerateAction::trigger()
{
  m_running = true;
  m_startvelocity = m_camera->getBaseVelocity();
  glm::vec4 rotatedaccel = glm::rotate(glm::mat4(1.0), m_camera->getRotation()[1],
                                glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_acceleration, 1.0);
  m_camera->setAcceleration(glm::vec3(rotatedaccel[0], rotatedaccel[1], rotatedaccel[2]));
}

bool CameraAccelerateAction::isRunning()
{
  return m_running;
}

bool CameraAccelerateAction::hasCompleted()
{
  if(m_isabsolute)
  {
    m_running = false;
    return true;
  }
  else
  {
    if(fabs(glm::length(m_camera->getVelocity()) - glm::length(m_camera->getBaseVelocity())) < 0.01)
    {
      m_running = false;
      m_camera->setAcceleration(glm::vec3(0.0, 0.0, 0.0));
      glm::vec4 rotatedvel = glm::rotate(glm::mat4(1.0), m_camera->getRotation()[1],
                                glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(m_camera->getBaseVelocity(), 1.0);
      m_camera->setVelocity(glm::vec3(rotatedvel[0], rotatedvel[1], rotatedvel[2]));
      return true;
    }
    else
      return false;
  }
}

//Depending on the addedtranslation based off of the change in time, the
//translation is updated.
void CameraAccelerateAction::update(float deltatime)
{
}
