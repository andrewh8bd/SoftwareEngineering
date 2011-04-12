#include "applicationframework.h"
#include "lightcycle.h"
#include "turnlightcycleaction.h"
#include "lightcycleaccelerateaction.h"
#include "turncameraaction.h"
#include "cameraaccelerateaction.h"
#include "lightcycleforwardaction.h"
#include "cameraforwardaction.h"
#include "ogl-math/glm/gtc/matrix_transform.hpp"
#include "ogl-math/glm/gtc/type_ptr.hpp"
#include <GL/glfw.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <sstream>

ApplicationFramework::ApplicationFramework(const unsigned int w, const unsigned int h)
  : m_windowwidth(w), m_windowheight(h), m_currentstate(MAIN_MENU), m_currentcamera(NULL)
{
}

void ApplicationFramework::initialize()
{
  //Initialize glfw (this creates our opengl context)
  glfwInit();
  
  //Create the window with 32bit color depth, 8 bit depth, and 0 bit stencil buffer
  //(we don't need stencil  buffer). It also puts it in a window instead of fullscreen.
  //It also makes the window the specified height and width.
	glfwOpenWindow(m_windowwidth, m_windowheight, 8, 8, 8, 8, 8, 0, GLFW_WINDOW);
	glMatrixMode(GL_PROJECTION);
  //Load the identity  matrix 
  glLoadIdentity();
  //Cute little perspective projection with near clip plane at z = 0 and far at z = 1000
  //90 degree field of view.
  glLoadMatrixf(glm::value_ptr(glm::mat4(glm::perspectiveFov(90.0f, static_cast<float>(m_windowwidth), static_cast<float>(m_windowheight), 0.0f, 1000.0f))));
	glMatrixMode(GL_MODELVIEW);
    //Load the identity matrix
  glLoadIdentity();
  
  //Initialize shit
  Renderer::getInstance()->initialize();
    
  //Switch to game state for now, since we don't have a menu.
  switchToGameState();
  std::cout<<"Derping"<<std::endl;
}

//Main loop runs in this.
void ApplicationFramework::run()
{
  //Used for fps counter, and time based updates
  float lasttime = glfwGetTime();
  float starttime = glfwGetTime();
  unsigned int fps = 0;
  //While a window exists
  while(glfwGetWindowParam(GLFW_OPENED))
  {
    //Update fps counter
    if(glfwGetTime() - starttime >= 1.0)
    {
      std::stringstream s;
      s<<"Light Cycle FPS: "<<fps;
      glfwSetWindowTitle(s.str().c_str());
      fps = 0;
      starttime = glfwGetTime();
    }
    else
    {
      fps++;
    }
    //clear the frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    switch(m_currentstate)
    {
      case MAIN_MENU:
        //nothing to see here, move along
        break;
      case GAME:
        //This isn't the switch case you're looking for.
        break;
      default:
        break;
    }
    //Update event handler and camera
    std::cout<<"Derping"<<std::endl;
    EventHandler::getInstance()->update(glfwGetTime() - lasttime);
    std::cout<<"Derping"<<std::endl;
    m_currentcamera->update(glfwGetTime() - lasttime);
    //Save camera matrix
    glPushMatrix();
    //Updates game objects
    for(std::vector<GameObject*>::iterator it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
      (*it)->update(glfwGetTime() - lasttime);
    }
    //Update renderer
    Renderer::getInstance()->render();
    //Restore camera matrix
    glPopMatrix();
    lasttime = glfwGetTime();
    
    //Swap dat double buffer
    glfwSwapBuffers();
    //Give other computer programs a chance to run.
    glfwSleep(0.01);
  }
}

void ApplicationFramework::switchToMainMenuState()
{
  m_currentstate = MAIN_MENU;
}

void ApplicationFramework::switchToGameState()
{
  //Change state
  m_currentstate = GAME;
  
  //Create interesting geometry(cubes for now) for the lightcycles
  std::vector<glm::vec3> vs;
  std::vector<glm::vec3> ns;
  std::vector<glm::vec2> ts;
  
  vs.push_back(glm::vec3(-0.5, 0.0, -1.0));
  vs.push_back(glm::vec3(-0.5, 0.0, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(-0.5, 0.0, -1.0));
  
  vs.push_back(glm::vec3(0.5, 0.0, -1.0));
  vs.push_back(glm::vec3(0.5, 0.0, 1.0));
  vs.push_back(glm::vec3(0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(0.5, 0.0, -1.0));
  
  vs.push_back(glm::vec3(-0.5, 0.0, -1.0));
  vs.push_back(glm::vec3(-0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(0.5, 0.0, -1.0));
  vs.push_back(glm::vec3(-0.5, 0.0, -1.0));
  
  vs.push_back(glm::vec3(-0.5, 0.0, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(0.5, 0.0, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.0, 1.0));
  
  vs.push_back(glm::vec3(-0.5, 0.0, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.0, -1.0));
  vs.push_back(glm::vec3(0.5, 0.0, -1.0));
  vs.push_back(glm::vec3(0.5, 0.0, -1.0));
  vs.push_back(glm::vec3(0.5, 0.0, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.0, 1.0));
  
  vs.push_back(glm::vec3(-0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(0.5, 0.5, -1.0));
  vs.push_back(glm::vec3(0.5, 0.5, 1.0));
  vs.push_back(glm::vec3(-0.5, 0.5, 1.0));
  
  ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  
  ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  
  ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  
  ns.push_back(glm::vec3(0.0, -1.0, 0.0));
  ns.push_back(glm::vec3(0.0, -1.0, 0.0));
  ns.push_back(glm::vec3(0.0, -1.0, 0.0));
  ns.push_back(glm::vec3(0.0, -1.0, 0.0));
  ns.push_back(glm::vec3(0.0, -1.0, 0.0));
  ns.push_back(glm::vec3(0.0, -1.0, 0.0));
  
  ns.push_back(glm::vec3(0.0, 1.0, 0.0));
  ns.push_back(glm::vec3(0.0, 1.0, 0.0));
  ns.push_back(glm::vec3(0.0, 1.0, 0.0));
  ns.push_back(glm::vec3(0.0, 1.0, 0.0));
  ns.push_back(glm::vec3(0.0, 1.0, 0.0));
  ns.push_back(glm::vec3(0.0, 1.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  //Create camera, as well as a few actions for it
  m_currentcamera = new Camera(glm::vec3(0.0, 2.0, 0.0), glm::vec3(45.0, 0.0, 0.0));
  TurnCameraAction* ca = new TurnCameraAction(m_currentcamera, RIGHT);
  TurnCameraAction* cb = new TurnCameraAction(m_currentcamera, LEFT);
  CameraForwardAction* cc = new CameraForwardAction(m_currentcamera, glm::vec3(0.0, 0.0, 6.0));
  CameraAccelerateAction* cd = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, 1.0), true);
  CameraAccelerateAction* ce = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, -1.0), false);
  CameraAccelerateAction* cf = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, 1.0), false);
  CameraAccelerateAction* cg = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, -1.0), true);
  
  //Create light cycle as well as a few actions for it
  GraphicsComponent *g = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
  
  LightCycle* l = new LightCycle(g, glm::vec3(0.0, 0.0, 0.0),
                                 glm::vec3(0.0, 0.0, 0.0), glm::vec4(1.0, 0.0, 0.0, 1.0));
  TurnLightCycleAction* a = new TurnLightCycleAction(l, RIGHT);
  TurnLightCycleAction* b = new TurnLightCycleAction(l, LEFT);
  LightCycleForwardAction* c = new LightCycleForwardAction(l, glm::vec3(0.0, 0.0, 6.0));
  LightCycleAccelerateAction* d = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, 1.0), true);
  LightCycleAccelerateAction* e = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, -1.0), false);
  LightCycleAccelerateAction* h = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, 1.0), false);
  LightCycleAccelerateAction* i = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, -1.0), true);
  //Create other bullshit so we can see that we are moving
  GraphicsComponent *asdf = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
  asdf->setTransformation(glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)));
  GraphicsComponent *sdf = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
  sdf->setTransformation(glm::translate(glm::mat4(1.0), glm::vec3(-1.0, 0.0, 3.0)));
  GraphicsComponent *df = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
  df->setTransformation(glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 3.0)));
  GraphicsComponent *f = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
  f->setTransformation(glm::translate(glm::mat4(1.0), glm::vec3(-3.0, 0.0, 3.0)));
  
  //Hand actions to eventhandler to be connected with keyboard events.
  m_gameobjects.push_back(l);
  EventHandler::getInstance()->createKeyboardEvent('A', KEY_DOWN, b);
  EventHandler::getInstance()->createKeyboardEvent('D', KEY_DOWN, a);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_PRESSED, d);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_RELEASED, e);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_PRESSED, i);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_RELEASED, h);
  EventHandler::getInstance()->createKeyboardEvent('A', KEY_DOWN, cb);
  EventHandler::getInstance()->createKeyboardEvent('D', KEY_DOWN, ca);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_PRESSED, cd);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_RELEASED, ce);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_PRESSED, cg);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_RELEASED, cf);
  //Or constant events that happen allllll the time
  EventHandler::getInstance()->createConstantEvent(c);
  EventHandler::getInstance()->createConstantEvent(cc);
  
  std::cout<<"Dumping"<<std::endl;
  EventHandler::getInstance()->dump();
  std::cout<<"Done"<<std::endl;
  EventHandler::getInstance()->createKeyboardEvent('A', KEY_DOWN, b);
  std::cout<<"Added some shit"<<std::endl;
  EventHandler::getInstance()->createKeyboardEvent('D', KEY_DOWN, a);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_PRESSED, d);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_RELEASED, e);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_PRESSED, i);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_RELEASED, h);
  EventHandler::getInstance()->createKeyboardEvent('A', KEY_DOWN, cb);
  EventHandler::getInstance()->createKeyboardEvent('D', KEY_DOWN, ca);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_PRESSED, cd);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_RELEASED, ce);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_PRESSED, cg);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_RELEASED, cf);
  //Or constant events that happen allllll the time
  EventHandler::getInstance()->createConstantEvent(c);
  EventHandler::getInstance()->createConstantEvent(cc);
  std::cout<<"Added some shit"<<std::endl;
  
  //Create Ground
    //Yeah right, not yet. BLACKNESS.
}

//Clean dat shit up
void ApplicationFramework::shutDown()
{
  EventHandler::getInstance()->dump();
  Renderer::getInstance()->dump();
  delete m_currentcamera;
  while(m_gameobjects.size() > 0)
  {
    delete m_gameobjects.back();
    m_gameobjects.pop_back();
  }
  glfwTerminate();
}
