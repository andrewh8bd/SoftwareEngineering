#ifndef CAMERAFORWARDACTION_H
#define CAMERAFORWARDACTION_H
#include "action.h"
#include "camera.h"

/*****************************************************************************/
/* Class: CameraForwardAction                                                */
/* Description: This makes a camera go forward with a constant velocity.     */
/*****************************************************************************/
class CameraForwardAction : public Action
{
  private:
  Camera* m_camera;
  bool m_running;
  glm::vec3 m_velocity;
  public:
  CameraForwardAction();
  CameraForwardAction(Camera* c, const glm::vec3& vel);
  ~CameraForwardAction();
  void trigger();
  bool isRunning();
  bool hasCompleted();
  void update(float deltatime);
};
#endif
