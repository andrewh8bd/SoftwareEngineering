#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "box2d.h"
#include <vector>

class PhysicsManager
{
  private:
  static PhysicsManager* m_instance;
  std::vector<Box2D*> m_components;
  PhysicsManager();
  
  public:
  ~PhysicsManager();
  static PhysicsManager* getInstance();
  void dump();
  void update();
  Box2D* createBox(const std::vector<glm::vec3>&);
};

#endif
