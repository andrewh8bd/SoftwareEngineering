#include "box2d.h"
#include <limits>
#include <fstream>
#include <cstdlib>
#include <iostream>

Box2D::Box2D() : m_transform(1.0)
{
}

Box2D::Box2D(const std::vector<glm::vec3>& vs)
{
  float maxx = std::numeric_limits<float>::min();
  float minx = std::numeric_limits<float>::max();
  float maxz = std::numeric_limits<float>::min();
  float minz = std::numeric_limits<float>::max();
  
  for(std::vector<glm::vec3>::const_iterator it = vs.begin(); it != vs.end(); it++)
  {
    if((*it)[0] > maxx) maxx = (*it)[0];
    if((*it)[0] < minx) minx = (*it)[0];
    if((*it)[2] > maxz) maxz = (*it)[2];
    if((*it)[2] < minz) minz = (*it)[2];
  }
  
  m_corners[0] = glm::vec2(maxx, maxz);
  m_corners[1] = glm::vec2(maxx, minz);
  m_corners[2] = glm::vec2(minx, minz);
  m_corners[3] = glm::vec2(minx, maxz);
  
}

Box2D::Box2D(const glm::vec2& a, const glm::vec2& b)
{
  m_corners[0] = a;
  m_corners[1] = a;
  m_corners[2] = b;
  m_corners[3] = b;
}

Box2D::~Box2D()
{
  m_colliders.clear();
}

bool Box2D::intersect(Box2D* l)
{
  glm::vec4 transformedcorners1[4];
  glm::vec4 transformedcorners2[4];
  
  transformedcorners1[0] = m_transform * glm::vec4(m_corners[0][0], 1.0, m_corners[0][1], 1.0);
  transformedcorners1[1] = m_transform * glm::vec4(m_corners[1][0], 1.0, m_corners[1][1], 1.0);
  transformedcorners1[2] = m_transform * glm::vec4(m_corners[2][0], 1.0, m_corners[2][1], 1.0);
  transformedcorners1[3] = m_transform * glm::vec4(m_corners[3][0], 1.0, m_corners[3][1], 1.0);
  transformedcorners2[0] = l->m_transform * glm::vec4(l->m_corners[0][0], 1.0, l->m_corners[0][1], 1.0);
  transformedcorners2[1] = l->m_transform * glm::vec4(l->m_corners[1][0], 1.0, l->m_corners[1][1], 1.0);
  transformedcorners2[2] = l->m_transform * glm::vec4(l->m_corners[2][0], 1.0, l->m_corners[2][1], 1.0);
  transformedcorners2[3] = l->m_transform * glm::vec4(l->m_corners[3][0], 1.0, l->m_corners[3][1], 1.0);
  
  for(int a=0; a<4; a++)
  {
    for(int b=0; b<4; b++)
    {
      if(lineIntersect(glm::vec2(transformedcorners1[a][0], transformedcorners1[a][2]),
                       glm::vec2(transformedcorners1[(a+1)%4][0], transformedcorners1[(a+1)%4][2]),
                       glm::vec2(transformedcorners2[b][0], transformedcorners2[b][2]),
                       glm::vec2(transformedcorners2[(b+1)%4][0], transformedcorners2[(b+1)%4][2])))
      {
        m_colliders.push_back(l);
        return true;
      }
    }
  }
  return false;
}

bool Box2D::lineIntersect(const glm::vec2& beg1, const glm::vec2& end1, const glm::vec2& beg2, const glm::vec2& end2)
{
  glm::vec2 a = beg1;
  glm::vec2 b = end1;
  glm::vec2 c = beg2;
  glm::vec2 d = end2;
  
  float rnum = (a[1]-c[1]) * (d[0]-c[0]) - (a[0]-c[0]) * (d[1]-c[1]);
  float rden = (b[0]-a[0]) * (d[1]-c[1]) - (b[1]-a[1]) * (d[0]-c[0]);
  float snum = (a[1]-c[1]) * (b[0]-a[0]) - (a[0]-c[0]) * (b[1]-a[1]);
  float sden = rden;
  
  if(rden == 0.0)
  {
    return false;
  }
  
  float r = rnum / rden;
  float s = snum / sden;
  
  if(r >= 0.0 && r <= 1.0 && s >= 0.0 && s <= 1.0)
    return true;
  return false;
}
void Box2D::setTransformation(const glm::mat4& a)
{ 
  m_transform = a;
}

glm::mat4 Box2D::getTransformation() const 
{
  return m_transform; 
}

std::vector<Box2D*>& Box2D::getColliders()
{
  return m_colliders;
}

void Box2D::setCorners(std::vector<glm::vec3>& vs)
{
  float maxx = std::numeric_limits<float>::min();
  float minx = std::numeric_limits<float>::max();
  float maxz = std::numeric_limits<float>::min();
  float minz = std::numeric_limits<float>::max();
  
  for(std::vector<glm::vec3>::const_iterator it = vs.begin(); it != vs.end(); it++)
  {
    if((*it)[0] > maxx) maxx = (*it)[0];
    if((*it)[0] < minx) minx = (*it)[0];
    if((*it)[2] > maxz) maxz = (*it)[2];
    if((*it)[2] < minz) minz = (*it)[2];
  }
  
  m_corners[0] = glm::vec2(maxx, maxz);
  m_corners[1] = glm::vec2(maxx, minz);
  m_corners[2] = glm::vec2(minx, minz);
  m_corners[3] = glm::vec2(minx, maxz);
}

void Box2D::clearColliders()
{
  m_colliders.clear();
}

glm::vec2* Box2D::getCorners()
{
  return m_corners;
}

void Box2D::setEnd(const glm::vec2& e)
{
  m_corners[2] = e;
  m_corners[3] = e;
}
