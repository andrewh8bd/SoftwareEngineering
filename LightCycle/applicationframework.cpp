#include "applicationframework.h"
#include "lightcycle.h"
#include "turnlightcycleaction.h"
#include "lightcycleaccelerateaction.h"
#include "turncameraaction.h"
#include "cameraaccelerateaction.h"
#include "lightcycleforwardaction.h"
#include "cameraforwardaction.h"
#include "physicsmanager.h"
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
  
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  
  //Initialize shit
  Renderer::getInstance()->initialize();
    
  //Switch to game state for now, since we don't have a menu.
  //switchToGameState();
  switchToMainMenuState();
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
		//The menu
		glViewport(0, 0, m_windowwidth, m_windowheight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(glm::mat4(glm::ortho(-1.0, 1.0, -1.0, 1.0))));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		Renderer::getInstance()->render();
        break;

      case GAME:
        //This isn't the switch case you're looking for.
        glViewport(0, 0, m_windowwidth / 2 ,m_windowheight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(glm::mat4(glm::perspectiveFov(90.0f, static_cast<float>(m_windowwidth / 2), static_cast<float>(m_windowheight), 1.0f, 1000.0f))));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        m_currentcamera->update(glfwGetTime() - lasttime);
        Renderer::getInstance()->render();
        
        
        glViewport(m_windowwidth / 2, 0, m_windowwidth / 2, m_windowheight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(glm::mat4(glm::perspectiveFov(90.0f, static_cast<float>(m_windowwidth / 2.0), static_cast<float>(m_windowheight), 1.0f, 1000.0f))));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        m_secondcamera->update(glfwGetTime() - lasttime);
        Renderer::getInstance()->render();
        
        break;
	  case OPTIONS:
		glViewport(0, 0, m_windowwidth, m_windowheight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(glm::mat4(glm::ortho(-1.0, 1.0, -1.0, 1.0))));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		Renderer::getInstance()->render();
		break;
	  case COLOR;
		//Where you choose your lightcycle color
		glViewport(0, 0, m_windowwidth, m_windowheight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(glm::mat4(glm::ortho(-1.0, 1.0, -1.0, 1.0))));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		Renderer::getInstance()->render();
		break;
      default:
        break;
    }
    //Update event handler and camera
    PhysicsManager::getInstance()->update();
    EventHandler::getInstance()->update(glfwGetTime() - lasttime);
    //Updates game objects
    for(std::vector<GameObject*>::iterator it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
      (*it)->update(glfwGetTime() - lasttime);
    }
    //Update renderer
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
  std::vector<glm::vec3> vs;
  std::vector<glm::vec3> ns;
  std::vector<glm::vec2> ts;
  //Load up Main Menu CHANGES HERE
  //Create textured square to fill the whole screen
  vs.push_back(glm::vec3(-1.0, -1.0, 0.0));
  vs.push_back(glm::vec3(-1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, -1.0, 0.0));
  vs.push_back(glm::vec3(-1.0, -1.0, 0.0));

  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));

  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, m_windowwidth / 2, m_windowheight, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 	GraphicsComponent *menu = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
	menu->addTexture(Renderer::getInstance()->loadAndGetTexture("LCycle_Menu.jpg"));
  //Actions!
  ChangeMenu* chng1 = new ChangeMenu(2); // 2 = Options
  ChangeMenu* chng2 = new ChangeMenu(3);   // 3 = Multi (COLORS)
  ChangeMenu* chng3 = new ChangeMenu(4);  // 4 = Single (COLORS)
  ChangeMenu* quitter = new ChangeMenu(7);	  //7 = quit
  //Click da buttons!  //Top Right x1,y1 Bottom Left x2,y2
  EventHandler::getInstance()-> createMouseClickHotspotEvent(281, 507, 762, 450, chng1); //Go to Options Menu!
  EventHandler::getInstance()-> createMouseClickHotspotEvent(281, 402, 524, 450, chng2);//Go to choose color (Multi)
  EventHandler::getInstance()-> createMouseClickHotspotEvent(40, 402, 281, 450, chng3); //Go to choose color (Single)
  EventHandler::getInstance()-> createMouseClickHotspotEvent(281, 507, 522, 557, quitter); //Quit the game :(
}

void ApplicationFramework::switchToOptions()
{
	std::vector<glm::vec3> vs;
  std::vector<glm::vec3> ns;
  std::vector<glm::vec2> ts;
  //Load up Main Menu CHANGES HERE
  //Create textured square to fill the whole screen
  vs.push_back(glm::vec3(-1.0, -1.0, 0.0));
  vs.push_back(glm::vec3(-1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, -1.0, 0.0));
  vs.push_back(glm::vec3(-1.0, -1.0, 0.0));

  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));

  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, m_windowwidth / 2, m_windowheight, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 	GraphicsComponent *menu = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
	menu->addTexture(Renderer::getInstance()->loadAndGetTexture("LCycle_Options.jpg"));
	ChangeMenu* chng = new ChangeMenu(1);

	//Click the buttons!  Top Right x1,y1 Bottom Left x2,y2
	EventHandler::getInstance()-> createMouseClickHotspotEvent(313, 520, 488, 570, chng); //Return to main menu

}

void ApplicationFramework::switchToColor(int numPlayers)
{
	m_currentstate = COLOR;
	std::vector<glm::vec3> vs;
  std::vector<glm::vec3> ns;
  std::vector<glm::vec2> ts;
  //Load up Main Menu CHANGES HERE
  //Create textured square to fill the whole screen
  vs.push_back(glm::vec3(-1.0, -1.0, 0.0));
  vs.push_back(glm::vec3(-1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, 1.0, 0.0));
  vs.push_back(glm::vec3(1.0, -1.0, 0.0));
  vs.push_back(glm::vec3(-1.0, -1.0, 0.0));

  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));
  ns.push_back(glm::vec3(0.0, 0.0, -1.0));

  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, m_windowwidth / 2, m_windowheight, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 	GraphicsComponent *menu = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
	menu->addTexture(Renderer::getInstance()->loadAndGetTexture("LCycle_Color.jpg"));

	ChangeMenu* chng = new ChangeMenu(1); //1 = main menu
	ChangeMenu* chng1 = new ChangeMenu(5);  //5 = Start game
	ChooseColor* clr = new ChooseColor(10);       //Actions for colors  10 = Red
	ChooseColor* clr1 = new ChooseColor(11);   //So many colors!    11 = Purple
	ChooseColor* clr2 = new ChooseColor(12); // 12 = Blue
	ChooseColor* clr3 = new ChooseColor(13); // 13 = Light Blue
	ChooseColor* clr4 = new ChooseColor(14);  //14 = Orange

	//Click the buttons!  Top Right x1,y1 Bottom Left x2,y2
	EventHandler::getInstance()-> createMouseClickHotspotEvent(48, 206, 138, 300, clr4); //Picked Orange
	EventHandler::getInstance()-> createMouseClickHotspotEvent(200, 206, 296, 300, clr);//Picked Red
	EventHandler::getInstance()-> createMouseClickHotspotEvent(355, 206, 453, 206, clr1); //Picked Purple
	EventHandler::getInstance()-> createMouseClickHotspotEvent(513, 206, 610, 300, clr2); //Picked Blue
	EventHandler::getInstance()-> createMouseClickHotspotEvent(654, 206, 748, 300, clr3);//Picked LightBlue
	EventHandler::getInstance()-> createMouseClickHotspotEvent(320, 340, 486, 390, chng1); //EnterGame
	EventHandler::getInstance()-> createMouseClickHotspotEvent(320, 517, 486, 568, chng); //Picked Blue
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
  m_currentcamera = new Camera(glm::vec3(0.0, 2.0, -25.0), glm::vec3(25.0, 0.0, 0.0));
  TurnCameraAction* ca = new TurnCameraAction(m_currentcamera, RIGHT);
  TurnCameraAction* cb = new TurnCameraAction(m_currentcamera, LEFT);
  CameraForwardAction* cc = new CameraForwardAction(m_currentcamera, glm::vec3(0.0, 0.0, 6.0));
  CameraAccelerateAction* cd = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, 1.0), true);
  CameraAccelerateAction* ce = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, -1.0), false);
  CameraAccelerateAction* cf = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, 1.0), false);
  CameraAccelerateAction* cg = new CameraAccelerateAction(m_currentcamera, glm::vec3(0.0, 0.0, -1.0), true);
  
  m_secondcamera = new Camera(glm::vec3(0.0, 2.0, 25.0), glm::vec3(25.0, 180.0, 0.0));
  TurnCameraAction* ca2 = new TurnCameraAction(m_secondcamera, RIGHT);
  TurnCameraAction* cb2 = new TurnCameraAction(m_secondcamera, LEFT);
  CameraForwardAction* cc2 = new CameraForwardAction(m_secondcamera, glm::vec3(0.0, 0.0, -6.0));
  CameraAccelerateAction* cd2 = new CameraAccelerateAction(m_secondcamera, glm::vec3(0.0, 0.0, -1.0), true);
  CameraAccelerateAction* ce2 = new CameraAccelerateAction(m_secondcamera, glm::vec3(0.0, 0.0, 1.0), false);
  CameraAccelerateAction* cf2 = new CameraAccelerateAction(m_secondcamera, glm::vec3(0.0, 0.0, -1.0), false);
  CameraAccelerateAction* cg2 = new CameraAccelerateAction(m_secondcamera, glm::vec3(0.0, 0.0, 1.0), true);
  //Create light cycle as well as a few actions for it
  GraphicsComponent *g = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
  g->setShaderProgram(Renderer::getInstance()->loadAndGetShader("lightcycle.vert", "lightcycle.frag"));
  g->addTexture(Renderer::getInstance()->loadAndGetTexture("blah.png"));
  g->addSamplerLocation(glGetUniformLocation(g->getShaderProgram(), "lctexture"));
  
  Box2D* gbox = PhysicsManager::getInstance()->createBox(vs);
  
  LightCycle* l = new LightCycle(g, gbox, glm::vec3(0.0, 0.0, -25.0),
                                 glm::vec3(0.0, 0.0, 0.0), glm::vec4(1.0, 0.0, 0.0, 1.0));
  l->addNewWall();
  TurnLightCycleAction* a = new TurnLightCycleAction(l, RIGHT);
  TurnLightCycleAction* b = new TurnLightCycleAction(l, LEFT);
  LightCycleForwardAction* c = new LightCycleForwardAction(l, glm::vec3(0.0, 0.0, 6.0));
  LightCycleAccelerateAction* d = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, 1.0), true);
  LightCycleAccelerateAction* e = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, -1.0), false);
  LightCycleAccelerateAction* h = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, 1.0), false);
  LightCycleAccelerateAction* i = new LightCycleAccelerateAction(l, glm::vec3(0.0, 0.0, -1.0), true);
  
  
  Box2D* gbox2 = PhysicsManager::getInstance()->createBox(vs);
  GraphicsComponent *g2 = Renderer::getInstance()->createStaticGraphicsComponent(vs, ns, ts);
  g2->setShaderProgram(Renderer::getInstance()->loadAndGetShader("lightcycle.vert", "lightcycle.frag"));
  g2->addTexture(Renderer::getInstance()->loadAndGetTexture("blah.png"));
  g2->addSamplerLocation(glGetUniformLocation(g2->getShaderProgram(), "lctexture"));
  
  LightCycle* l2 = new LightCycle(g2, gbox2, glm::vec3(0.0, 0.0, 25.0),
                                 glm::vec3(0.0, 180.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 1.0));
  l2->addNewWall();
  TurnLightCycleAction* a2 = new TurnLightCycleAction(l2, RIGHT);
  TurnLightCycleAction* b2 = new TurnLightCycleAction(l2, LEFT);
  LightCycleForwardAction* c2 = new LightCycleForwardAction(l2, glm::vec3(0.0, 0.0, -6.0));
  LightCycleAccelerateAction* d2 = new LightCycleAccelerateAction(l2, glm::vec3(0.0, 0.0, -1.0), true);
  LightCycleAccelerateAction* e2 = new LightCycleAccelerateAction(l2, glm::vec3(0.0, 0.0, 1.0), false);
  LightCycleAccelerateAction* h2 = new LightCycleAccelerateAction(l2, glm::vec3(0.0, 0.0, -1.0), false);
  LightCycleAccelerateAction* i2 = new LightCycleAccelerateAction(l2, glm::vec3(0.0, 0.0, 1.0), true);
  //Create other bullshit so we can see that we are moving
  
  //Hand actions to eventhandler to be connected with keyboard events.
  m_gameobjects.push_back(l);
  m_gameobjects.push_back(l2);
  EventHandler::getInstance()->createKeyboardEvent('A', KEY_PRESSED, b);
  EventHandler::getInstance()->createKeyboardEvent('D', KEY_PRESSED, a);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_PRESSED, d);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_RELEASED, e);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_PRESSED, i);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_RELEASED, h);
  EventHandler::getInstance()->createKeyboardEvent('A', KEY_PRESSED, cb);
  EventHandler::getInstance()->createKeyboardEvent('D', KEY_PRESSED, ca);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_PRESSED, cd);
  EventHandler::getInstance()->createKeyboardEvent('W', KEY_RELEASED, ce);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_PRESSED, cg);
  EventHandler::getInstance()->createKeyboardEvent('S', KEY_RELEASED, cf);
  //Or constant events that happen allllll the time
  EventHandler::getInstance()->createConstantEvent(c);
  EventHandler::getInstance()->createConstantEvent(cc);
  
  
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_LEFT, KEY_PRESSED, b2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_RIGHT, KEY_PRESSED, a2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_UP, KEY_PRESSED, d2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_UP, KEY_RELEASED, e2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_DOWN, KEY_PRESSED, i2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_DOWN, KEY_RELEASED, h2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_LEFT, KEY_PRESSED, cb2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_RIGHT, KEY_PRESSED, ca2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_UP, KEY_PRESSED, cd2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_UP, KEY_RELEASED, ce2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_DOWN, KEY_PRESSED, cg2);
  EventHandler::getInstance()->createKeyboardEvent(GLFW_KEY_DOWN, KEY_RELEASED, cf2);
  //Or constant events that happen allllll the time
  EventHandler::getInstance()->createConstantEvent(c2);
  EventHandler::getInstance()->createConstantEvent(cc2);
  
  std::vector<glm::vec3> wall1vs;
  std::vector<glm::vec3> wall2vs;
  std::vector<glm::vec3> wall3vs;
  std::vector<glm::vec3> wall4vs;
  std::vector<glm::vec3> wall1ns;
  std::vector<glm::vec3> wall2ns;
  std::vector<glm::vec3> wall3ns;
  std::vector<glm::vec3> wall4ns;
  std::vector<glm::vec2> wall1ts;
  std::vector<glm::vec2> wall2ts;
  std::vector<glm::vec2> wall3ts;
  std::vector<glm::vec2> wall4ts;
  wall1vs.push_back(glm::vec3(-50.0, 0.0, -50.0));
  wall1vs.push_back(glm::vec3(-50.0, 0.0, 50.0));
  wall1vs.push_back(glm::vec3(-50.0, 50.0, 50.0));
  wall1vs.push_back(glm::vec3(-50.0, 50.0, 50.0));
  wall1vs.push_back(glm::vec3(-50.0, 50.0, -50.0));
  wall1vs.push_back(glm::vec3(-50.0, 0.0, -50.0));
  
  wall2vs.push_back(glm::vec3(50.0, 0.0, -50.0));
  wall2vs.push_back(glm::vec3(50.0, 0.0, 50.0));
  wall2vs.push_back(glm::vec3(50.0, 50.0, 50.0));
  wall2vs.push_back(glm::vec3(50.0, 50.0, 50.0));
  wall2vs.push_back(glm::vec3(50.0, 50.0, -50.0));
  wall2vs.push_back(glm::vec3(50.0, 0.0, -50.0));
  
  wall3vs.push_back(glm::vec3(-50.0, 0.0, -50.0));
  wall3vs.push_back(glm::vec3(-50.0, 50.0, -50.0));
  wall3vs.push_back(glm::vec3(50.0, 50.0, -50.0));
  wall3vs.push_back(glm::vec3(50.0, 50.0, -50.0));
  wall3vs.push_back(glm::vec3(50.0, 0.0, -50.0));
  wall3vs.push_back(glm::vec3(-50.0, 0.0, -50.0));
  
  wall4vs.push_back(glm::vec3(-50.0, 0.0, 50.0));
  wall4vs.push_back(glm::vec3(-50.0, 50.0, 50.0));
  wall4vs.push_back(glm::vec3(50.0, 50.0, 50.0));
  wall4vs.push_back(glm::vec3(50.0, 50.0, 50.0));
  wall4vs.push_back(glm::vec3(50.0, 0.0, 50.0));
  wall4vs.push_back(glm::vec3(-50.0, 0.0, 50.0));
  
  
  wall1ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  wall1ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  wall1ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  wall1ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  wall1ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  wall1ns.push_back(glm::vec3(1.0, 0.0, 0.0));
  
  wall2ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  wall2ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  wall2ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  wall2ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  wall2ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  wall2ns.push_back(glm::vec3(-1.0, 0.0, 0.0));
  
  wall3ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall3ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall3ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall3ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall3ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall3ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  
  wall4ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall4ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall4ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall4ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall4ns.push_back(glm::vec3(0.0, 0.0, 1.0));
  wall4ns.push_back(glm::vec3(0.0, 0.0, 1.0));
    
  wall1ts.push_back(glm::vec2(0.0, 0.0));
  wall1ts.push_back(glm::vec2(0.0, 1.0));
  wall1ts.push_back(glm::vec2(1.0, 1.0));
  wall1ts.push_back(glm::vec2(1.0, 1.0));
  wall1ts.push_back(glm::vec2(1.0, 0.0));
  wall1ts.push_back(glm::vec2(0.0, 0.0));
  
  wall2ts.push_back(glm::vec2(0.0, 0.0));
  wall2ts.push_back(glm::vec2(0.0, 1.0));
  wall2ts.push_back(glm::vec2(1.0, 1.0));
  wall2ts.push_back(glm::vec2(1.0, 1.0));
  wall2ts.push_back(glm::vec2(1.0, 0.0));
  wall2ts.push_back(glm::vec2(0.0, 0.0));
  
  wall3ts.push_back(glm::vec2(0.0, 0.0));
  wall3ts.push_back(glm::vec2(0.0, 1.0));
  wall3ts.push_back(glm::vec2(1.0, 1.0));
  wall3ts.push_back(glm::vec2(1.0, 1.0));
  wall3ts.push_back(glm::vec2(1.0, 0.0));
  wall3ts.push_back(glm::vec2(0.0, 0.0));
  
  wall4ts.push_back(glm::vec2(0.0, 0.0));
  wall4ts.push_back(glm::vec2(0.0, 1.0));
  wall4ts.push_back(glm::vec2(1.0, 1.0));
  wall4ts.push_back(glm::vec2(1.0, 1.0));
  wall4ts.push_back(glm::vec2(1.0, 0.0));
  wall4ts.push_back(glm::vec2(0.0, 0.0));
  
  PhysicsManager::getInstance()->createBox(wall1vs);  
  PhysicsManager::getInstance()->createBox(wall2vs);  
  PhysicsManager::getInstance()->createBox(wall3vs);  
  PhysicsManager::getInstance()->createBox(wall4vs);  
  GraphicsComponent *wall1 = Renderer::getInstance()->createStaticGraphicsComponent(wall1vs, wall1ns, wall1ts);
  wall1->setShaderProgram(Renderer::getInstance()->loadAndGetShader("wall.vert", "wall.frag"));
  wall1->addTexture(Renderer::getInstance()->loadAndGetTexture("blah.png"));
  wall1->addSamplerLocation(glGetUniformLocation(wall1->getShaderProgram(), "lctexture"));
  
  PhysicsManager::getInstance()->createBox(vs);
  GraphicsComponent *wall2 = Renderer::getInstance()->createStaticGraphicsComponent(wall2vs, wall2ns, wall2ts);
  wall2->setShaderProgram(Renderer::getInstance()->loadAndGetShader("wall.vert", "wall.frag"));
  wall2->addTexture(Renderer::getInstance()->loadAndGetTexture("blah.png"));
  wall2->addSamplerLocation(glGetUniformLocation(wall2->getShaderProgram(), "lctexture"));
  
  GraphicsComponent *wall3 = Renderer::getInstance()->createStaticGraphicsComponent(wall3vs, wall3ns, wall3ts);
  wall3->setShaderProgram(Renderer::getInstance()->loadAndGetShader("wall.vert", "wall.frag"));
  wall3->addTexture(Renderer::getInstance()->loadAndGetTexture("blah.png"));
  wall3->addSamplerLocation(glGetUniformLocation(wall3->getShaderProgram(), "lctexture"));
  
  GraphicsComponent *wall4 = Renderer::getInstance()->createStaticGraphicsComponent(wall4vs, wall4ns, wall4ts);
  wall4->setShaderProgram(Renderer::getInstance()->loadAndGetShader("wall.vert", "wall.frag"));
  wall4->addTexture(Renderer::getInstance()->loadAndGetTexture("blah.png"));
  wall4->addSamplerLocation(glGetUniformLocation(wall4->getShaderProgram(), "lctexture"));
  //Create Ground
    //Yeah right, not yet. BLACKNESS.
}

//Clean dat shit up
void ApplicationFramework::shutDown()
{
  EventHandler::getInstance()->dump();
  Renderer::getInstance()->dump();
  PhysicsManager::getInstance()->dump();
  delete m_currentcamera;
  if(m_secondcamera != NULL)
    delete m_secondcamera;
  while(m_gameobjects.size() > 0)
  {
    delete m_gameobjects.back();
    m_gameobjects.pop_back();
  }
  glfwTerminate();
}
