#ifndef ACTION_H
#define ACTION_H
#include <iostream>

//Dummy action to see if the event handler is working. Will be the abstract base for
//all actions.
class Action
{
  public:
  Action() {}
  virtual ~Action() {}
  virtual void trigger() {std::cout<<"Event Triggered"<<std::endl;}
  virtual bool isRunning() {return false;}
  virtual bool hasCompleted() {return true;}
};

#endif
