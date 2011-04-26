#ifndef CHOOSECOLOR_H
#define CHOOSECOLOR_H
#include "action.h"
#include "appplicationframework.h"

/*****************************************************************************/
/* Class: ChooseColor														 */
/* Description: Choose the color of the lightcycle									 */
/*****************************************************************************/
class ChooseColor : public Action
{
  private:
	  bool m_choose;
  public:
	  ChangeMenu(const int choose); // 1 = Main Menu, 2 = Options, 3 = Multi, 4 = Single, 5 = Start Game, 7 = quit
	  bool hasCompleted();
};

#endif
