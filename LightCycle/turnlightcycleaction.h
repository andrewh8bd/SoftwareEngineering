#ifndef TURNLIGHTCYCLEACTION_H
#define TURNLIGHTCYCLEACTION_H
#include "lightcycle.h"
#include "action.h"

/*****************************************************************************/
/* Class: TurnLightCycleAction                                               */
/* Description: Long name, I know but I like things to read like english.    */
/*              Obviously this is an action that makes a provided light cycle*/
/*              to turn left or right. You can specify the time it should    */
/*              take to get through a 90 degree turn, with a default of 0.05 */
/*              seconds. Trigger turns m_running true and initializes the    */
/*              turning process by stopping it's velocity and adding an      */
/*              angular velocity to the light cycle. It is done when the time*/
/*              is reached and consequently when it has finished a 90 degree */
/*              turn. Pretty sweet ya might say?                             */
/*****************************************************************************/
class TurnLightCycleAction : public Action
{
  private:
  LightCycle *m_cycle;
  DIRECTION m_direction;
  float m_timetaken;
  float m_turntime;
  bool m_running;
  static bool m_alreadyturning;
  glm::vec3 m_oldvelocity;
  glm::vec3 m_oldrotation;
  public:
  TurnLightCycleAction(LightCycle* c = NULL, const DIRECTION d = RIGHT, const float tt = 0.05);
  ~TurnLightCycleAction();
  void trigger();
  bool isRunning();
  bool hasCompleted();
  void update(float deltatime);
};

#endif
