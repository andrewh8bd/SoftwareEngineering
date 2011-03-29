#include "keyboardevent.h"
#include <GL/glfw.h>

KeyboardEvent::KeyboardEvent() : m_keycode(0), m_keytype(KEY_DOWN)
{
}

KeyboardEvent::~KeyboardEvent()
{
}

void KeyboardEvent::setKey(const int c)
{
  m_keycode = c;
}

void KeyboardEvent::setType(const KEY_TYPE k)
{
  m_keytype = k;
}

bool KeyboardEvent::queryFor()
{
  if(m_keytype == KEY_DOWN)
    return glfwGetKey(m_keycode) == GLFW_PRESS;
  else if(m_keytype == KEY_UP)
    return glfwGetKey(m_keycode) == GLFW_RELEASE;
}
