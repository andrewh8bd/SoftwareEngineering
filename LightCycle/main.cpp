#include "applicationframework.h"

int main()
{
  ApplicationFramework A;
  A.initialize();
  A.run();
  A.shutDown();
  return 0;
}
