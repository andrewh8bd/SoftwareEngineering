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
	  //I would like a way to get the event to return a variable to the application_framework, do you know a way to do that?
	  //Basically I just want the events to send a trigger back to the application framework code to activate a switchcase to call functions to changemenu
;
  public:

};

#endif
