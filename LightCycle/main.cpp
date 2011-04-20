#include "applicationframework.h"

//This main function need not do anything, because everything is taken care of
//in the three functions ApplicationFramework::initialize(),
//ApplicationFramework::run(), and ApplicationFramework::shutDown()

int main()
{
  ApplicationFramework A(1200, 800);
  A.initialize();
  A.run();
  A.shutDown();
  return 0;
}
