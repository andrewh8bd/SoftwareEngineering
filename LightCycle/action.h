#ifndef ACTION_H
#define ACTION_H

//Enough digits? No.
const float PI = 3.141592653589793238462643383279;

//Directions to turn. Idk why this is here, probably cause I used it in two places
enum DIRECTION {RIGHT, LEFT};

//Abstract base for actions.
class Action
{
  protected:
  //It may be abstract, but everything needs to know if it's running or not.
  bool m_running;
  public:
  Action() {}
  virtual ~Action() {}
  virtual void trigger() = 0;
  virtual bool isRunning() = 0;
  virtual bool hasCompleted() = 0;
  virtual void update(float deltatime) = 0;
};

#endif
