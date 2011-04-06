#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H
#include "event.h"

//Everything pertaining to keyboard events
enum KEY_TYPE {KEY_DOWN, KEY_UP, KEY_PRESSED, KEY_RELEASED};
class KeyboardEvent : public Event
{
  private:
  int m_keycode;
  KEY_TYPE m_keytype;
  int m_laststate; //1 down, 0 up
  public:
  KeyboardEvent();
  ~KeyboardEvent();
  void setKey(const int);
  void setType(const KEY_TYPE);
  bool queryFor();
};

#endif
