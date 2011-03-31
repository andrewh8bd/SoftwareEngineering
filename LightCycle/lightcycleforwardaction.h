#ifndef LIGHTCYCLEFORWARDACTION_H
#define LIGHTCYCLEFORWARDACTION_H
#include "action.h"
#include "lightcycle.h"

/*****************************************************************************/
/* Class: LightCycleForwardAction                                            */
/* Description: This makes light cycles go forward with a constant velocity. */
/*****************************************************************************/
class LightCycleForwardAction : public Action
{
  private:
  LightCycle* m_cycle;
  bool m_running;
  glm::vec3 m_velocity;
  public:
  LightCycleForwardAction();
  LightCycleForwardAction(LightCycle* l, const glm::vec3 &vel);
  ~LightCycleForwardAction();
  void trigger();
  bool isRunning();
  bool hasCompleted();
  void update(float deltatime);
};

#endif
