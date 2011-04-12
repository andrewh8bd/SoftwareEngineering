#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include "keyboardevent.h"
#include "mouseevent.h"
#include "action.h"
#include <vector>
#include <map>

//Connects an event to an action. I don't often connect pointers, but when I do: I create structs.
struct EventToAction
{
  Event* e;
  Action* a;
};

/*****************************************************************************/
/*Class: EventHandler                                                        */
/*Description: Handles all events and the actions that are associated with   */
/*             them. Click = mouse click, hotspot = mouse in an area, key-   */
/*             board = key down or up.                                       */ 
/*****************************************************************************/

class EventHandler
{
  private:
  std::vector<EventToAction> m_events;
  static EventHandler* m_instance;
  static std::map<int, bool> m_keysdown;
  
  EventHandler();
  public:
  ~EventHandler();
  static EventHandler* getInstance();
  KeyboardEvent* createKeyboardEvent(const int, const KEY_TYPE, Action*);
  MouseEvent* createMouseClickEvent(const int, Action*);
  MouseEvent* createMouseHotspotEvent(const unsigned int, const unsigned int, 
                                      const unsigned int, const unsigned int, Action*);
  MouseEvent* createMouseClickHotspotEvent(const int, const unsigned int, const unsigned int,
                                           const unsigned int, const unsigned int, Action*);
  void createConstantEvent(Action*);
  void update(float deltatime);
  void dump();
  std::vector<EventToAction> getEvents() const;
};

#endif
