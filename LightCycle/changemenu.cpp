#include "action.h"
#include "appplicationframework.h"
#include "changemenu.h"
//Choose is used to select which menu
ChangeMenu::ChangeMenu(const int choose) : m_choose(choose);
{
}

ChangeMenu::~ChangeMenu()
{
}

bool ChangeMenu::hasCompleted()
{
	switch(m_choose)
	{
	//Go to Main Menu
	case 1:
		*this -> switchToMainMenu();
		break;
	//Go to Options
	case 2:
		*this -> switchToOptions();
		break;
	//Go to Single (Color)
	case 3:
		*this -> switchToColors(1);
		break;
	//Go to Multi (Color)
	case 4:
		*this -> switchToColor(2);
		break;

	case 5:
		*this -> switchToGameState();
		break;

	case 7:
		*this -> shutdown();
		break;

	default:
		return false;
		break;
	}
	return true;
}