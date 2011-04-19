#ifndef CAMERA_H
#define CAMERA_H
#include "ogl-math/glm/glm.hpp"
#include "gameobject.h"
/*****************************************************************************/
/* Class: Camera                                                             */
/* Description: This class holds all information pertaining to a camera in a */
/*              scene. It holds the camera's transformation (that the inverse*/
/*              will be used to rotate and translate the scene around the    */
/*              camera. It also has velocity, acceleration, both linearly and*/
/*              angularly. We can update each one of these things as well as */
/*              position and rotation inherited from GameObject. Update takes*/
/*              all the rotation and position information and constructs a   */
/*              matrix to be sent to openGL.                                 */
/*****************************************************************************/
class Camera : public GameObject
{
  private:
  glm::mat4 m_transformation;
  glm::vec3 m_velocity;
  glm::vec3 m_acceleration;
  glm::vec3 m_angularvelocity;
  glm::vec3 m_angularacceleration;
  glm::vec3 m_distancetofocus;
  glm::vec3 m_startingvelocity;
  bool m_alreadyturning;
  public:
  Camera(const glm::vec3 p = glm::vec3(0.0, 0.0, 0.0), const glm::vec3 r = glm::vec3(0.0, 0.0, 0.0));
  ~Camera();
  void setTransformation(const glm::mat4&);
  glm::mat4 getTransformation() const;
  void setPosition(const glm::vec3&);
  glm::vec3 getPosition() const;
  void setRotation(const glm::vec3&);
  glm::vec3 getRotation() const;
  void setVelocity(const glm::vec3&);
  glm::vec3 getVelocity() const;
  void setAcceleration(const glm::vec3&);
  glm::vec3 getAngularVelocity() const;
  void setAngularVelocity(const glm::vec3&);
  glm::vec3 getAngularAcceleration() const;
  void setAngularAcceleration(const glm::vec3&);
  glm::vec3 getAcceleration() const;
  glm::vec3 getDistanceToFocus() const;
  glm::vec3 getBaseVelocity() const;
  void setBaseVelocity(const glm::vec3&);
  void update(const float);
  void setAlreadyTurning(const bool);
  bool getAlreadyTurning() const;
};

#endif
