#include <iostream>
#include "ringbuffer.hpp"
#include <stack>

class testClass {
private:
public:
  static int val;
  int num;
  testClass (){
    num = val;
    val++;
    // std::cout << "const" << std::endl;
  };
  ~testClass(){
    // std::cout << "dest" << std::endl;
  }
};
int testClass::val = 0;
std::ostream& operator<<(std::ostream& os, const testClass& tc){
  os << tc.val << ":" << tc.num;
  return os;
}

int main(int argc, char const *argv[]) {
  RingBuffer<testClass, 4> rb;
  rb.print();

  //push/pop front
  // rb.push_front(testClass());
  // rb.push_front(testClass());
  // rb.push_front(testClass());
  // rb.push_front(testClass());
  // rb.push_front(testClass()) << "\n";
  // rb.print();
  // std::cout << rb.pop_front() << std::endl;
  // rb.print();
  // std::cout << rb.pop_front() << std::endl;
  // rb.print();
  // std::cout << rb.pop_front() << std::endl;
  // rb.print();
  // std::cout << rb.pop_front() << std::endl;
  // rb.print();

  //push/pop back
  // rb.push_back(testClass());
  // rb.push_back(testClass());
  // rb.push_back(testClass());
  // rb.push_back(testClass());
  // rb.push_back(testClass());
  // std::cout << "\n" << std::endl;
  // rb.print();
  // std::cout << rb.pop_back() << std::endl;
  // rb.print();
  // std::cout << rb.pop_back() << std::endl;
  // rb.print();
  // std::cout << rb.pop_back() << std::endl;
  // rb.print();
  // std::cout << rb.pop_back() << std::endl;
  // rb.print();

  // push/ pop mixed
  // rb.push_front(testClass());
  // rb.push_back(testClass());
  // rb.push_front(testClass());
  // rb.push_back(testClass());
  // rb.push_front(testClass());
  // rb.push_back(testClass());
  // std::cout << "\n" << std::endl;
  // rb.print();
  // std::cout << rb.pop_back() << std::endl;
  // rb.print();
  // std::cout << rb.pop_front() << std::endl;
  // rb.print();
  // std::cout << rb.pop_front() << std::endl;
  // rb.print();
  // std::cout << rb.pop_back() << std::endl;

  //overflow front / back + Exceptions
  rb.push_front(testClass());
  rb.push_front(testClass());
  rb.push_front(testClass());
  rb.push_front(testClass());
  std::cout << "\n" << std::endl;
  rb.print();

  std::cout << rb.pop_back() << std::endl;
  std::cout << rb.pop_back() << std::endl;
  std::cout << rb.pop_back() << std::endl;
  rb.print();

  rb.push_front(testClass());
  rb.push_front(testClass());
  rb.push_front(testClass());
  std::cout << "\n" << std::endl;
  rb.print();

  std::cout << rb.pop_back() << std::endl;
  std::cout << rb.pop_back() << std::endl;
  std::cout << rb.pop_back() << std::endl;
  rb.print();

  rb.push_back(testClass());
  rb.push_back(testClass());
  rb.push_back(testClass());
  std::cout << "\n" << std::endl;
  rb.print();

  std::cout << rb.pop_front() << std::endl;
  std::cout << rb.pop_front() << std::endl;
  std::cout << rb.pop_front() << std::endl;
  std::cout << rb.pop_front() << std::endl;
  rb.print();

  try {
    rb.pop_back();
    std::cout << "This should not be printed!" << std::endl;
  }
  catch (std::exception& rangeError) {
    std::cout << "Error: " << rangeError.what() << std::endl;
  }

  try {
    rb.pop_front();
    std::cout << "This should not be printed!" << std::endl;
  }
  catch (std::exception& rangeError) {
    std::cout << "Error: " << rangeError.what() << std::endl;
  }


  return 0;
}
