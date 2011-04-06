#ifndef LIGHTCYCLEACCELERATEACTION_H
#define LIGHTCYCLEACCELERATEACTION_H
#include "action.h"
#include "lightcycle.h"
#include "ogl-math/glm/glm.hpp"
#include "ogl-math/glm/gtc/matrix_transform.hpp"

class LightCycleAccelerateAction : public Action
{
  private:
  LightCycle* m_cycle;
  glm::vec3 m_acceleration;
  glm::vec3 m_startvelocity;
  bool m_isabsolute;
  glm::vec3 m_time;
  public:
  LightCycleAccelerateAction();
  LightCycleAccelerateAction(LightCycle* l, const glm::vec3 &acc, const bool absolute);
  ~LightCycleAccelerateAction();
  void trigger();
  bool isRunning();
  bool hasCompleted();
  void update(float deltatime);
};

#endif
