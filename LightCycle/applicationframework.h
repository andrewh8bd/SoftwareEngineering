#ifndef APPLICATIONFRAMEWORK_H
#define APPLICATIONFRAMEWORK_H
#include "renderer.h"
#include "eventhandler.h"

enum APP_STATE {MAIN_MENU, GAME};
class ApplicationFramework
{
  private:
  unsigned int m_windowwidth;
  unsigned int m_windowheight;
  APP_STATE m_currentstate;
  Renderer* m_renderer;
  EventHandler* m_eventhandler;
  public:
  ApplicationFramework(const unsigned int, const unsigned int);
  void initialize();
  APP_STATE getCurrentState();
  void switchToMainMenuState();
  void switchToGameState();
  void shutDown();
};

#endif
