#ifndef CAMERAACCELERATEACTION_H
#define CAMERAACCELERATEACTION_H
#include "action.h"
#include "camera.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"

class CameraAccelerateAction : public Action
{
  private:
  Camera* m_camera;
  glm::vec3 m_acceleration;
  glm::vec3 m_startvelocity;
  bool m_isabsolute;
  glm::vec3 m_time;
  public:
  CameraAccelerateAction();
  CameraAccelerateAction(Camera* l, const glm::vec3 &acc, const bool absolute);
  ~CameraAccelerateAction();
  void trigger();
  bool isRunning();
  bool hasCompleted();
  void update(float deltatime);
};

#endif
