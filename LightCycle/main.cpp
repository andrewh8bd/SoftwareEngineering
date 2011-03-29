#include "renderer.h"
#include "ogl-math/glm/glm.hpp"
#include "eventhandler.h"
#include <vector>
#include <gl/glfw.h>
#include <iostream>
int main()
{
  Renderer r;
  EventHandler h;
  std::vector<glm::vec3> verts;
  std::vector<glm::vec3> norms;
  std::vector<glm::vec2> texs;
  
  glfwInit();
	glfwOpenWindow(800, 800, 8, 8, 8, 8, 8, 0, GLFW_WINDOW);
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
  
  h.createKeyboardEvent('W', KEY_DOWN, new Action());
  h.createKeyboardEvent('A', KEY_DOWN, new Action());
  h.createKeyboardEvent('S', KEY_DOWN, new Action());
  h.createKeyboardEvent('D', KEY_DOWN, new Action());
  h.createMouseClickEvent(GLFW_MOUSE_BUTTON_LEFT, new Action());
  h.createMouseClickHotspotEvent(GLFW_MOUSE_BUTTON_RIGHT, 0, 0, 200, 200, new Action());
  h.createMouseHotspotEvent(201, 201, 500, 500, new Action());
  
  verts.push_back(glm::vec3(0.0, 0.0, 0.0));
  verts.push_back(glm::vec3(0.0, 1.0, 0.0));
  verts.push_back(glm::vec3(1.0, 1.0, 0.0));
  verts.push_back(glm::vec3(1.0, 1.0, 0.0));
  verts.push_back(glm::vec3(1.0, 0.0, 0.0));
  verts.push_back(glm::vec3(0.0, 0.0, 0.0));
  
  norms.push_back(glm::vec3(0.0, 0.0, 1.0));
  norms.push_back(glm::vec3(0.0, 0.0, 1.0));
  norms.push_back(glm::vec3(0.0, 0.0, 1.0));
  norms.push_back(glm::vec3(0.0, 0.0, 1.0));
  norms.push_back(glm::vec3(0.0, 0.0, 1.0));
  norms.push_back(glm::vec3(0.0, 0.0, 1.0));
  
  texs.push_back(glm::vec2(0.0, 0.0));
  texs.push_back(glm::vec2(0.0, 1.0));
  texs.push_back(glm::vec2(1.0, 1.0));
  texs.push_back(glm::vec2(1.0, 1.0));
  texs.push_back(glm::vec2(1.0, 0.0));
  texs.push_back(glm::vec2(0.0, 0.0));
  
  r.initialize();
  
  GraphicsComponent* g = r.createStaticGraphicsComponent(verts, norms, texs);
  std::vector<unsigned int> textures;
  textures.push_back(r.loadAndGetTexture("blah.png"));
  textures.push_back(r.loadAndGetTexture("blah2.png"));
  g->setTextures(textures);
  g->setShaderProgram(r.loadAndGetShader("myshader.vert", "myshader.frag"));
  std::vector<unsigned int> samplers;
  samplers.push_back(glGetUniformLocation(g->getShaderProgram(), "my_texture"));
  samplers.push_back(glGetUniformLocation(g->getShaderProgram(), "my_texture2"));
  g->setSamplerLocations(samplers);
  
  while(glfwGetWindowParam(GLFW_OPENED))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    r.render();
    h.update(0.0);
    glfwSwapBuffers();
  }
  glfwTerminate();
  return 0;
}
