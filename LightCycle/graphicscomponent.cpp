#include "graphicscomponent.h"
#include <iostream>
GraphicsComponent::GraphicsComponent() : m_vbobeginindex(0), m_vboendindex(0), m_shaderid(0), 
                                         m_graphicsstate(STATIC), m_transform(1.0)
{
}

GraphicsComponent::GraphicsComponent(const GraphicsComponent& g) : m_vbobeginindex(g.m_vbobeginindex), m_vboendindex(g.m_vboendindex),
                                                                   m_shaderid(g.m_shaderid), m_graphicsstate(g.m_graphicsstate), 
                                                                   m_transform(g.m_transform), m_samplerlocations(g.m_samplerlocations),
                                                                   m_textureids(g.m_textureids), m_vertexinformation(g.m_vertexinformation)
{
}

bool GraphicsComponent::isVisible() const
{
  return true;
}

unsigned int GraphicsComponent::getVBOBegin() const
{
  return m_vbobeginindex;
}

void GraphicsComponent::setVBOBegin(const unsigned int index)
{
  m_vbobeginindex = index;
}

unsigned int GraphicsComponent::getVBOEnd() const
{
  return m_vboendindex;
}

void GraphicsComponent::setVBOEnd(const unsigned int index)
{
  m_vboendindex = index;
}

unsigned int GraphicsComponent::getShaderProgram() const
{
  return m_shaderid;
}

void GraphicsComponent::setShaderProgram(const unsigned int id)
{
  m_shaderid = id;
}

std::vector<VertexInformation> GraphicsComponent::getVertexInformation() const
{
  return m_vertexinformation;
}

void GraphicsComponent::setVertexInformation(const std::vector<VertexInformation>& vi)
{
  m_vertexinformation = vi;
}

glm::mat4 GraphicsComponent::getTransformation() const
{
  return m_transform;
}

void GraphicsComponent::setTransformation(const glm::mat4& m)
{
  m_transform = m;
}

std::vector<unsigned int> GraphicsComponent::getTextures() const
{
  return m_textureids;
}

void GraphicsComponent::setTextures(const std::vector<unsigned int>& t)
{
  m_textureids = t;
}

unsigned int GraphicsComponent::getSamplerLocation(unsigned int index) const
{
  if(index > m_samplerlocations.size() - 1)
    std::cout<<"Invalid sampler location index"<<std::endl;
  return m_samplerlocations[index];
}

void GraphicsComponent::setSamplerLocations(const std::vector<unsigned int>& t)
{
  m_samplerlocations = t;
}

GRAPHICS_STATE GraphicsComponent::getGraphicsState() const
{
  return m_graphicsstate;
}

void GraphicsComponent::setGraphicsState(const GRAPHICS_STATE g)
{
  m_graphicsstate = g;
}
