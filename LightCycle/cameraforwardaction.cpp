#include "Cameraforwardaction.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include <iostream>
CameraForwardAction::CameraForwardAction() : m_camera(NULL), m_velocity(glm::vec3(0.0, 0.0, 0.0)), m_running(false)
{
}

CameraForwardAction::CameraForwardAction(Camera* c = NULL, const glm::vec3& vel = glm::vec3(0.0, 0.0, 0.0)) : m_camera(c), m_running(false), m_velocity(vel)
{
}

CameraForwardAction::~CameraForwardAction()
{
  m_camera = NULL;
}

void CameraForwardAction::trigger()
{
  m_running = true;
  m_camera->setVelocity(m_velocity);
}

bool CameraForwardAction::isRunning()
{
  return m_running;
}

bool CameraForwardAction::hasCompleted()
{
  return false;
}

//Lulz
void CameraForwardAction::update(float deltatime)
{
  glm::vec3 addedtranslation(0.0, 0.0, 0.0);
  glm::vec3 vel = m_camera->getVelocity();
  glm::vec3 acc = m_camera->getAcceleration();
  addedtranslation = vel * deltatime + acc * deltatime * deltatime * 0.5f;
  
  m_camera->setPosition(m_camera->getPosition() + glm::vec3(addedtranslation[0], addedtranslation[1],
                                          addedtranslation[2]));
}
