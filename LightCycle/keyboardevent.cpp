#include "keyboardevent.h"
#include <GL/glfw.h>
#include <iostream>

KeyboardEvent::KeyboardEvent() : m_keycode(0), m_keytype(KEY_DOWN)
{
}

KeyboardEvent::~KeyboardEvent()
{
}

void KeyboardEvent::setKey(const int c)
{
  m_keycode = c;
  m_laststate = glfwGetKey(m_keycode) == GLFW_PRESS;
}

void KeyboardEvent::setType(const KEY_TYPE k)
{
  m_keytype = k;
}

bool KeyboardEvent::queryFor()
{
  bool retval = false;
  if(m_keytype == KEY_DOWN)
    retval = glfwGetKey(m_keycode) == GLFW_PRESS;
  else if(m_keytype == KEY_UP)
    retval = glfwGetKey(m_keycode) == GLFW_RELEASE;
  else if(m_keytype == KEY_PRESSED)
    retval = glfwGetKey(m_keycode) == GLFW_PRESS && m_laststate    == 0;
  else if(m_keytype == KEY_RELEASED)
  {
    bool keynotdown = glfwGetKey(m_keycode) == GLFW_RELEASE;
    retval = keynotdown && m_laststate == 1;
  }
  m_laststate = glfwGetKey(m_keycode) == GLFW_PRESS;
  
  return retval;
}
