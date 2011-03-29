#include "eventhandler.h"
EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
  for(std::vector<EventToAction>::iterator it=m_events.begin(); it != m_events.end(); it++)
  {
    delete it->a;
    delete it->e;
  }
}

KeyboardEvent* EventHandler::createKeyboardEvent(const int key, const KEY_TYPE type, Action* a)
{
  EventToAction ea;
  KeyboardEvent* k = new KeyboardEvent();
  
  k->setKey(key);
  k->setType(type);
  ea.e = k;
  ea.a = a;
  m_events.push_back(ea);
  return k;
}

MouseEvent* EventHandler::createMouseClickEvent(const int click, Action* a)
{
  EventToAction ea;
  MouseEvent* m = new MouseEvent();
  
  m->setButton(click);
  m->setType(CLICK);
  ea.e = m;
  ea.a = a;
  m_events.push_back(ea);
  return m;
}

MouseEvent* EventHandler::createMouseHotspotEvent(const unsigned int x1, const unsigned int y1, 
                                                  const unsigned int x2, const unsigned int y2, Action* a)
{
  EventToAction ea;
  MouseEvent* m = new MouseEvent();
  m->setHotspot(x1, y1, x2, y2);
  m->setType(HOTSPOT);
  ea.e = m;
  ea.a = a;
  m_events.push_back(ea);
  return m;
}
MouseEvent* EventHandler::createMouseClickHotspotEvent(const int click, const unsigned int x1, const unsigned int y1,
                                                       const unsigned int x2, const unsigned int y2, Action* a)
{

  EventToAction ea;
  MouseEvent* m = new MouseEvent();
  m->setHotspot(x1, y1, x2, y2);
  m->setButton(click);
  m->setType(HOTSPOT_CLICK);
  ea.e = m;
  ea.a = a;
  m_events.push_back(ea);
  return m;
}

void EventHandler::update(float deltatime)
{
  for(std::vector<EventToAction>::iterator it = m_events.begin(); it!= m_events.end(); it++)
  {
    if(it->e->queryFor() && !it->a->isRunning())
    {
      it->a->trigger();
    }
  }
}
