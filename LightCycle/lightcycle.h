#ifndef LIGHTCYCLE_H
#define LIGHTCYCLE_H
#include "ogl-math/glm/glm.hpp"
#include "graphicscomponent.h"
#include "gameobject.h"
#include "lightcyclewall.h"
#include "box2d.h"
#include <vector>

/*****************************************************************************/
/* Class: LightCycle                                                         */
/* Description: This class holds all information pertaining to a light cycle */
/*              game object. It has a color, velocity, and acceleration      */
/*              both linearly and angularly. It also has a handle on a grap- */
/*              hics component that will be a visible lightcycle, that can be*/
/*              manipulated by shader to change color. Everything about the  */
/*              lightcycle can be changed but changes aren't committed until */
/*              updated is called and the graphic component's transformation */
/*              matrix is updated.                                           */
/*****************************************************************************/
class LightCycle : public GameObject
{
  private:
  glm::vec4 m_color;
  glm::vec3 m_velocity;
  glm::vec3 m_acceleration;
  glm::vec3 m_angularvelocity;
  glm::vec3 m_angularacceleration;
  glm::vec3 m_startingvelocity;
  GraphicsComponent* m_graphicscomponent;
  Box2D* m_boundingbox;
  std::vector<LightCycleWall*> m_walls; //The one one the back is the one connected 
                                        //to the light cycle.
  bool m_alreadyturning;
  
  public:
  LightCycle(GraphicsComponent* g = NULL, Box2D* box = NULL, const glm::vec3& pos = glm::vec3(0.0, 0.0, 0.0),
             const glm::vec3& rot = glm::vec3(0.0, 0.0, 0.0), const glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
  ~LightCycle();
  void setColor(const glm::vec4&);
  glm::vec4 getColor() const;
  void setPosition(const glm::vec3&);
  void addTranslation(const glm::vec3&);
  glm::vec3 getPosition() const;
  void setRotation(const glm::vec3&);
  void addRotation(const glm::vec3&);
  glm::vec3 getRotation() const;
  void setVelocity(const glm::vec3&);
  glm::vec3 getVelocity() const;
  void setAcceleration(const glm::vec3&);
  glm::vec3 getAngularVelocity() const;
  void setAngularVelocity(const glm::vec3&);
  glm::vec3 getAngularAcceleration() const;
  void setAngularAcceleration(const glm::vec3&);
  glm::vec3 getAcceleration() const;
  void setTransformation(const glm::mat4&);
  glm::mat4 getTransformation();
  glm::vec3 getBaseVelocity() const;
  void setBaseVelocity(const glm::vec3&);
  void addNewWall();
  void update(const float deltatime);
  void setAlreadyTurning(const bool);
  bool getAlreadyTurning() const;
};

#endif
