#include "applicationframework.h"

ApplicationFramework::ApplicationFramework(const unsigned int w = 640, const unsigned int h = 480)
  : m_windowwidth(w), m_windowheight(h), m_currentstate(MAIN_MENU), m_renderer(NULL), m_eventhandler(NULL)
{
}

void ApplicationFramework::initialize()
{
  glfwInit();
	glfwOpenWindow(m_windowwidth, m_windowheight, 8, 8, 8, 8, 8, 0, GLFW_WINDOW);
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
  
  m_renderer = new Renderer();
  m_eventhandler = new EventHandler();
  m_renderer->initialize();
  
  switchToGameState();
}

void ApplicationFramework::run()
{
  while(glfwGetWindowParam(GLFW_OPENED))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch(m_currentstate)
    {
      case MAIN_MENU:
        break;
      case GAME:
        break;
      default:
    }
    
    m_renderer.render();
    m_eventhandler.update(0.0);
    
    glfwSwapBuffers();
    glfwSleep(0.01);
  }
}

void ApplicationFramework::switchToMainMenuState()
{
  m_currentstate = MAIN_MENU;
}

void ApplicationFramework::switchToGameState()
{
  m_currentstate = GAME;
  //Create Light Cycle
  //Create Actions For Light Cycle
  //Create Ground
}

void ApplicationFramework::shutDown()
{
  glfwTerminate();
}
