#include <iostream>

// A class wrapping the former main function.
class Workarround{
  
public:
  //The old main function is now a member of the Workarround class.
  int main(void) {
   std::cout << "Hello world!" << std::endl;
   return 0;
  }

};

/* The new main function calling the old main method which is now a member of the
*  Workarround class. new == better. */
int main(void) {
  std::cout << "---start---" << std::endl;
  Workarround w;
  w.main();
  std::cout << "---end---" << std::endl;
  return 0;
}
