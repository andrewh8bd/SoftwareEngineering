#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include "keyboardevent.h"
#include "mouseevent.h"
#include "action.h"
#include <vector>

struct EventToAction
{
  Event* e;
  Action* a;
};

/*****************************************************************************/
/*Class: EventHandler                                                        */
/*Description: Handles all events and the actions that are associated with   */
/*             them.                                                         */
/*****************************************************************************/

class EventHandler
{
  private:
  std::vector<EventToAction> m_events;
  public:
  EventHandler();
  ~EventHandler();
  KeyboardEvent* createKeyboardEvent(const int, const KEY_TYPE, Action*);
  MouseEvent* createMouseClickEvent(const int, Action*);
  MouseEvent* createMouseHotspotEvent(const unsigned int, const unsigned int, 
                                      const unsigned int, const unsigned int, Action*);
  MouseEvent* createMouseClickHotspotEvent(const int, const unsigned int, const unsigned int,
                                           const unsigned int, const unsigned int, Action*);
  void update(float deltatime);
};

#endif
