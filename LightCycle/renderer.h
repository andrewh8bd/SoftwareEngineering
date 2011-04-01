#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <GL/GLee.h>
#include <GL/gl.h>
#include <string>
#include "graphicscomponent.h"
#include "ogl-math/glm/glm.hpp"

//Lets us get a byte offset to be used with the vbos
#define BUFFER_OFFSET(i) ((char*)NULL + i)

//2 meg buffer size
const int MAX_BUFFER_SIZE = 2097152;


/*****************************************************************************/
/* Class: Renderer                                                           */
/* Description: This class holds all information needed to manage all things */
/*              shown to the screen. It gives the possibility to create      */
/*              static objects that do not change over time based off of     */
/*              provieded geometry information, or dynamic objects that have */
/*              the ability to change their vertex information over time.    */
/*              Everything graphical is done using a patch stored in VBOs    */
/*              (Vertex Buffer Objects) and the distinct indices for certain */
/*              objects are stored in them, and then are sent to the GPU to  */
/*              render them. We can also create texture objects to be given  */
/*              to the objects, as well as a shader program. The Render func */
/*              should be called once every frame so the graphics are updated*/
/*              on time.                                                     */
/*****************************************************************************/
class Renderer
{
  private:
    std::vector<GraphicsComponent*> m_graphicscomponents;
    unsigned int m_staticvertexbufferobject;
    unsigned int m_dynamicvertexbufferobject;
    unsigned int m_staticindexbufferobject;
    unsigned int m_dynamicindexbufferobject;
    
    unsigned int m_numstaticindices;
    unsigned int m_numdynamicindices;
    Renderer();
    static Renderer* m_instance;
  public:
    ~Renderer();
    static Renderer* getInstance();
    void initialize();
    GraphicsComponent* createStaticGraphicsComponent(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&,
                                                     const std::vector<glm::vec2>&);
    GraphicsComponent* createDynamicGraphicsComponent(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&,
                                                      const std::vector<glm::vec2>&);
    unsigned int loadAndGetShader(std::string, std::string);
    unsigned int loadAndGetTexture(std::string);
    void render();
    void dump();
};

#endif
