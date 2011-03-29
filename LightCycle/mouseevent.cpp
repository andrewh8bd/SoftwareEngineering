#include "mouseevent.h"
#include <GL/glfw.h>
MouseEvent::MouseEvent() : m_xposition(-1), m_yposition(-1), m_scrollwheel(-1), m_button(0),
                           m_minx(-1), m_miny(-1), m_maxx(-1), m_maxy(-1), m_type(CLICK)
{
}
 
MouseEvent::~MouseEvent()
{
}

void MouseEvent::setType(const MOUSE_TYPE m)
{
  m_type == m;
}

void MouseEvent::setButton(const int c)
{
  m_button = c;
}

void MouseEvent::setHotspot(const int x1, const int y1, const int x2, const int y2)
{
  m_minx = x1;
  m_miny = y1;
  m_maxx = x2;
  m_maxy = y2;
}

bool MouseEvent::queryFor()
{
  if(m_type == CLICK)
  {
    return (glfwGetMouseButton(m_button) == GLFW_PRESS);
  }
  else if(m_type == HOTSPOT)
  {
    glfwGetMousePos(&m_xposition, &m_yposition);
    if(m_xposition >= m_minx && m_xposition <= m_maxx &&
       m_yposition >= m_miny && m_yposition <= m_maxy)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else if(m_type == HOTSPOT_CLICK)
  {
    if(m_xposition >= m_minx && m_xposition <= m_maxx &&
       m_yposition >= m_miny && m_yposition <= m_maxy)
    {
      return (glfwGetMouseButton(m_button) == GLFW_PRESS);
    }
  }
  //Should never get here.
  return false;
}
