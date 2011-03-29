#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "event.h"

//Everything pertaining to mouse events
enum MOUSE_TYPE {CLICK, HOTSPOT, HOTSPOT_CLICK};
class MouseEvent : public Event
{
  private:
  int m_xposition;
  int m_yposition;
  int m_scrollwheel;
  int m_button;
  int m_maxx;
  int m_maxy;
  int m_minx;
  int m_miny;
  MOUSE_TYPE m_type;
  public:
  MouseEvent();
  ~MouseEvent();
  void setButton(const int);
  void setHotspot(const int, const int, const int, const int);
  void setType(const MOUSE_TYPE);
  bool queryFor();
};

#endif
