#ifndef EVENT_H
#define EVENT_H

/*****************************************************************************/
/*Class: Event                                                               */
/*Description: Creates an abstract base class for all types of events to be  */
/*             handled by the event manager.                                 */
/*****************************************************************************/

class Event
{
  public:
  Event() {}
  virtual ~Event() {}
  virtual bool queryFor() = 0;
};

#endif
