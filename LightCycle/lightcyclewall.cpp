#include "lightcyclewall.h"
#include <GL/GLee.h>

LightCycleWall::LightCycleWall() : m_color(glm::vec4(1.0, 1.0, 1.0, 1.0)), m_graphicscomponent(NULL)
{
}

LightCycleWall::LightCycleWall(GraphicsComponent* g, const glm::vec4& color)
{
  m_graphicscomponent = g;
  m_color = color;
}

void LightCycleWall::setEndPoint(const glm::vec3& p)
{
  std::vector<VertexInformation> vi = m_graphicscomponent->getVertexInformation();
  
  vi[1].px = p[0];
  vi[2].px = p[0]; vi[2].pz = p[2];
  
  vi[3].px = p[0]; vi[3].pz = p[2];
  vi[4].px = p[0];
  
  vi[6].px = p[0]; vi[6].pz = p[2];
  vi[7].pz = p[2];
  
  vi[10].pz = p[2];
  vi[11].px = p[0]; vi[1].pz = p[2];
  glBindBuffer(GL_ARRAY_BUFFER, m_graphicscomponent->getVBOHandle());
  glBufferSubData(GL_ARRAY_BUFFER, m_graphicscomponent->getVBOBegin() * 32, vi.size()*32, &vi[0].px);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
