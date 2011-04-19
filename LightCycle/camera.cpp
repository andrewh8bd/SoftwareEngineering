#include "camera.h"
#include "GL/gl.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include "ogl-math/glm/gtc/type_ptr.hpp"
#include <iostream>

Camera::Camera(const glm::vec3 p, const glm::vec3 r) : GameObject(p, r), m_transformation(1.0), m_distancetofocus(p), m_alreadyturning(false)
{
}

Camera::~Camera()
{
}

void Camera::setPosition(const glm::vec3& p)
{
  m_position = p;
}

glm::vec3 Camera::getPosition() const
{
  return m_position;
}

void Camera::setRotation(const glm::vec3& v)
{
  m_rotation = v;
}

glm::vec3 Camera::getRotation() const
{
  return m_rotation;
}

void Camera::setVelocity(const glm::vec3& v)
{
  m_velocity = v;
}

glm::vec3 Camera::getVelocity() const
{
  return m_velocity;
}

void Camera::setAcceleration(const glm::vec3& v)
{
  m_acceleration = v;
}

glm::vec3 Camera::getAcceleration() const
{
  return m_acceleration;
}

glm::vec3 Camera::getAngularVelocity() const
{
  return m_angularvelocity;
}

void Camera::setAngularVelocity(const glm::vec3& v)
{
  m_angularvelocity = v;
}

glm::vec3 Camera::getAngularAcceleration() const
{
  return m_angularacceleration;
}

void Camera::setAngularAcceleration(const glm::vec3& v)
{
  m_angularacceleration = v;
}

void Camera::setTransformation(const glm::mat4& t)
{
  m_transformation = t;
}

glm::mat4 Camera::getTransformation() const
{
  return m_transformation;
}

//New matrix is made out of -1 * position and -1 * rotation to make it seem like
//the camera is actully moving rather than the scene moving around the camera.
void Camera::update(const float deltatime) 
{
  glm::mat4 newtrans(1.0);
  
  newtrans = glm::rotate(newtrans, -m_rotation[0], glm::vec3(1.0, 0.0, 0.0));
  newtrans = glm::rotate(newtrans, -m_rotation[1], glm::vec3(0.0, 1.0, 0.0));
  newtrans = glm::rotate(newtrans, -m_rotation[2], glm::vec3(0.0, 0.0, 1.0));
  newtrans = glm::translate(newtrans, -m_position);
  m_transformation = newtrans;
  glLoadMatrixf(glm::value_ptr(m_transformation));
}

glm::vec3 Camera::getDistanceToFocus() const
{
  return m_distancetofocus;
}

void Camera::setBaseVelocity(const glm::vec3& v)
{
  m_startingvelocity = v;
}

glm::vec3 Camera::getBaseVelocity() const
{
  return m_startingvelocity;
}

void Camera::setAlreadyTurning(const bool a)
{
  m_alreadyturning = a;
}

bool Camera::getAlreadyTurning() const
{
  return m_alreadyturning;
}
