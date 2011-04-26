#ifndef CHANGEMENU_H
#define CHANGEMENU_H
#include "action.h"
#include "appplicationframework.h"

/*****************************************************************************/
/* Class: ChangeMenu														 */
/* Description: Changes the menu state										 */
/*****************************************************************************/
class ChangeMenu : public Action
{
  private:
	  bool m_running;
  public:
	  ChangeMenu(const int choose); // 1 = Main Menu, 2 = Options, 3 = Multi, 4 = Single, 5 = Start Game, 7 = quit
	  bool hasCompleted();
};

#endif
