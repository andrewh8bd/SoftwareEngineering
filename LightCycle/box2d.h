#ifndef BOX2D_H
#define BOX2D_H
#include "ogl-math/glm/glm.hpp"
#include <vector>

class Box2D
{
  private:
  glm::vec2 m_corners[4];
  glm::mat4 m_transform;
  std::vector<Box2D*> m_colliders;
  
  bool lineIntersect(const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec2&);
  
  public:
  Box2D();
  Box2D(const std::vector<glm::vec3>& vs);
  Box2D(const glm::vec2&, const glm::vec2&);
  ~Box2D();
  bool intersect(Box2D*);
  void setTransformation(const glm::mat4& a);
  void setCorners(std::vector<glm::vec3>& vs);
  glm::vec2* getCorners();
  glm::mat4 getTransformation() const;
  std::vector<Box2D*>& getColliders();
  void clearColliders();
  void setEnd(const glm::vec2& e);
};

#endif
