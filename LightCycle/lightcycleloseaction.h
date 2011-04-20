#ifndef LIGHTCYCLELOSEACTION_H
#define LIGHTCYCLELOSEACTION_H
#include "action.h"
#include "lightcycle.h"
#include "camera.h"

class LightCycleLoseAction : public Action
{
  private:
    LightCycle* m_cycle;
    Camera* m_camera;
    float m_time;
    float m_elapsedtime;
    bool m_running;
    glm::vec3 m_cameravelocity;
  public:
    LightCycleLoseAction();
    LightCycleLoseAction(LightCycle* l, Camera* c, const float t);
    ~LightCycleLoseAction();
    void trigger();
    bool isRunning();
    bool hasCompleted();
    void update(float deltatime);
};

#endif
