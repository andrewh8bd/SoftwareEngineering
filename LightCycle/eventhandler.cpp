#include "eventhandler.h"
#include <iostream>

EventHandler* EventHandler::m_instance = NULL;
EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

EventHandler* EventHandler::getInstance()
{
  if(m_instance == NULL)
    m_instance = new EventHandler;
  return m_instance;
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

void EventHandler::createConstantEvent(Action* a)
{
  EventToAction ea;
  ea.a = a;
  ea.e = NULL;
  m_events.push_back(ea);
}

void EventHandler::update(float deltatime)
{
  //If there are active actions, update them!
  //Check the not active ones to see if their events were triggered!
  for(std::vector<EventToAction>::iterator it = m_events.begin(); it!= m_events.end(); it++)
  {
    if((it->e == NULL || it->e->queryFor()) && !it->a->isRunning())
    {
      it->a->trigger();
    }
    if(it->a->isRunning())
    {
      if(!it->a->hasCompleted())
      {
        it->a->update(deltatime);
      }
    }
  }
}

void EventHandler::dump()
{
  for(std::vector<EventToAction>::iterator it=m_events.begin(); it != m_events.end(); it++)
  {
    delete it->a;
    delete it->e;
  }
  delete m_instance;
}
