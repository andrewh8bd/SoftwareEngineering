#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H
#include <vector>
#include "ogl-math/glm/glm.hpp"

struct VertexInformation
{
  float px, py, pz;
  float nx, ny, nz;
  float tx, ty;
};
/*****************************************************************************/
/* Class: GraphicsComponent                                                  */
/* Description: This class holds all information needed to show something    */
/*              graphical to the screen. It holds the beginning and ending   */
/*              indices, to show where it's vertex information is on the     */
/*              graphics card. It also has an id to the shader program that  */
/*              is used on it. Graphics state basically defines whether a    */
/*              certain graphics component stays with static (unchanging)    */
/*              vertices throughout its use, or dynamic. If it is dynamic    */
/*              we will hold a vector of client side vertex information so   */
/*              we can easily update it and send it to the graphics card     */
/*              rather than having to query the graphics card for the info.  */
/*              This class will also hold a vector of all the ids of the     */
/*              textures used for the graphics component.                    */
/*****************************************************************************/
enum GRAPHICS_STATE {STATIC, DYNAMIC};
class GraphicsComponent
{
  private:
  unsigned int m_vbobeginindex;
  unsigned int m_vboendindex;
  unsigned int m_shaderid;
  GRAPHICS_STATE m_graphicsstate;
  std::vector<VertexInformation> m_vertexinformation;
  std::vector<unsigned int> m_textureids;
  std::vector<unsigned int> m_samplerlocations;
  glm::mat4 m_transform;
  
  public:
  GraphicsComponent();
  GraphicsComponent(const GraphicsComponent&);
  bool isVisible() const;
  unsigned int getVBOBegin() const;
  void setVBOBegin(const unsigned int);
  unsigned int getVBOEnd() const;
  void setVBOEnd(const unsigned int);
  unsigned int getShaderProgram() const;
  void setShaderProgram(const unsigned int);
  std::vector<VertexInformation> getVertexInformation() const;
  void setVertexInformation(const std::vector<VertexInformation>&);
  glm::mat4 getTransformation() const;
  void setTransformation(const glm::mat4&);
  std::vector<unsigned int> getTextures() const;
  void setTextures(const std::vector<unsigned int>&);
  unsigned int getSamplerLocation(unsigned int) const;
  void setSamplerLocations(const std::vector<unsigned int>&);
  GRAPHICS_STATE getGraphicsState() const;
  void setGraphicsState(const GRAPHICS_STATE);
};

#endif
