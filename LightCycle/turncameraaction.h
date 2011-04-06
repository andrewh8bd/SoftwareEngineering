#ifndef TURNCAMERAACTION_H
#define TURNCAMERAACTION_H
#include "action.h"
#include "camera.h"
/*****************************************************************************/
/* Class: TurnLightCycleAction                                               */
/* Description: Long name, I know but I like things to read like english.    */
/*              Obviously this is an action that makes a provided camera     */
/*              to turn left or right. You can specify the time it should    */
/*              take to get through a 90 degree turn, with a default of 0.05 */
/*              seconds. Trigger turns m_running true and initializes the    */
/*              turning process by stopping it's velocity and adding an      */
/*              angular velocity to the camera. It is done when the time     */
/*              is reached and consequently when it has finished a 90 degree */
/*              turn. Pretty sweet ya might say?                             */
/*              This does the same thing as the light cycle one. I could've  */
/*              made them the same but I didn't.                             */
/*****************************************************************************/
class TurnCameraAction : public Action
{
  private:
  Camera *m_camera;
  DIRECTION m_direction;
  float m_timetaken;
  float m_turntime;
  static bool m_alreadyturning;
  glm::vec3 m_oldvelocity;
  glm::vec3 m_oldrotation;
  glm::vec3 m_oldacceleration;
  bool m_running;
  public:
  TurnCameraAction(Camera* c = NULL, const DIRECTION d = RIGHT, const float tt = 0.05);
  ~TurnCameraAction();
  void trigger();
  bool isRunning();
  bool hasCompleted();
  void update(float deltatime);
};
#endif
