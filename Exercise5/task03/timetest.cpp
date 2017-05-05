#include <iostream>
#include "stack.hpp"
#include "stopwatch.hpp"

#define MEASURETIME( description, repetitions, instructions2test)\
  { StopWatch stopwatch ;\
  stopwatch.start();\
  for (int i = 0; i < repetitions; i++) {\
    instructions2test\
  }\
  double t = stopwatch.stop();\
  std::cout << "My computer requires " << t << " seconds to execute "\
  << description << " " << repetitions << " times" << std::endl;};


Stack get(const Stack s){return s;}

int main(int argc, char const *argv[]) {
  Stack s1(100000);
  Stack *s;
  s1 = 15;
  // MEASURETIME( "FILL THE STACK", 100000 , s1.push(i);)
  // MEASURETIME( "Copy assignment test", 10000 , { s = new Stack(s1);delete s; s = new Stack(s1); delete s;s1 = s1;})
  // MEASURETIME( "Move assignment test", 10000 , { s1 = get(s1);})
  return 0;
}
