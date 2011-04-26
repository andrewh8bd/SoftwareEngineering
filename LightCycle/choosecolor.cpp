#include "action.h"
#include "appplicationframework.h"
#include "choosecolor.h"
//Choose is used to select which menu
ChooseColor::ChooseColor(const int choose) : m_choose(choose);
{
}

ChooseColor::~ChooseColor()
{
}

bool ChooseColor::hasCompleted()
{
	switch(m_choose)
	{
	//Picked Red
	case 10:
		break;
	//Picked Purple
	case 11:
		break;
	//Picked Blue
	case 12:
		break;
	//Picked Light Blue
	case 13:
		break;
	//Picked Orange
	case 14:
		break;

	default:
		return false;
		break;
	}
	return true;
}