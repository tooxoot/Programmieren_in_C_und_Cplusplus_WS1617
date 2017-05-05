#include <iostream>

/*
* Replaces the Makro with a variable definition of given type with given name.
* Also declares a getter and setter method.
*
* @param name The declared variable's name.
* @param type The declared variable's type.
*/
#define MAKEVAR(name, type)  \
type name; \
void set_ ## name(type val) { name = val; } \
type get_ ## name(void) { return name; }

MAKEVAR(weight, int)
MAKEVAR(price, float)

int main(void) {
  set_weight(100);
  set_price(1.25);
  std::cout << "Weight: " << get_weight() << ", Price: " << get_price() << std::endl;
}
