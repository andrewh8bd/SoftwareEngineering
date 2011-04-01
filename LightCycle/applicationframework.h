#ifndef APPLICATIONFRAMEWORK_H
#define APPLICATIONFRAMEWORK_H
#include "renderer.h"
#include "eventhandler.h"
#include "gameobject.h"
#include "camera.h"

/*****************************************************************************/
/* Class: ApplicationFramework                                               */
/* Description: This class holds the base control structure for the game, and*/
/*              is the grand central station for state changes and calling   */
/*              of update functions. It creates a window, destroys a window, */
/*              provides initialization and updating for different defined   */
/*              states.                                                      */
/*****************************************************************************/
enum APP_STATE {MAIN_MENU, GAME};
class ApplicationFramework
{
  private:
  unsigned int m_windowwidth;
  unsigned int m_windowheight;
  APP_STATE m_currentstate;
  Renderer* m_renderer;
  
  std::vector<GameObject*> m_gameobjects;
  Camera* m_currentcamera;
  public:
  ApplicationFramework(const unsigned int w = 640, const unsigned int h = 480);
  void initialize();
  void run();
  void switchToMainMenuState();
  void switchToGameState();
  void shutDown();
};

#endif
