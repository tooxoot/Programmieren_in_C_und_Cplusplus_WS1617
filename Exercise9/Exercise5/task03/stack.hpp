// Decalration of class Stack.
// Member functions are defined in stack.cpp.
// Prevent multiple inclunions.
#ifndef STACK_H
#define STACK_H

/**
* A class implementing a last in - first out Stack based on an array.
*/
class Stack{
private:
  int *arr;                 /**< Pointer to the underlying array representing the stack.*/
  int maximumCapacity;      /**< The stack's maximum size.*/
  int currentSize;          /**< The stack's current size.*/

  /*
  * Tis function copies the values of the passed stack.
  * It is only called by the cpoy constructor and assignment.
  *
  * @param copiedStack A reference to the copied stack.
  */
  void copy(const Stack &copiedStack);

  /*
  * Question: I was intending to implement a shared function for the move operations
  * as such as the copy function does for the copy operations. I was not able to
  * do so. Is there a way to implement a function that does?
  * (Look at the source file for my atempt) */
  // void move(Stack &&s);

public:
  /*
  * The default constructor. It defaults to Stack(10).
  */
  Stack();

  /*
  * This constructor initializes the Stack witch a given maximum capacity.
  *
  * @param: maxCapacity The maximum capacity of the initialized stack as int.
  */
  Stack(int maxCapacity);

  /*
  * This is the copy constructor which copies the values of a referenced stack.
  * Prints a signal when called.
  *
  * @param copiedStack A reference to the copied stack.
  */
  Stack(const Stack &copiedStack);

  /*
  * This is the move constructor which moves the values of a referenced stack to
  * the memory of the newly initialized stack.
  * Prints a signal when called.
  *
  * @param movedStack A rvalue reference to the moved stack.
  */
  Stack(Stack &&movedStack);

  /*
  * The deconstructor deleting the underlying array.
  * Prints a signal when called.
  */
  ~Stack();

  /*
  * This is the copy assignment which copies the values of a referenced stack.
  * Prints a signal when called.
  *
  * @param copiedStack A reference to the copied stack.
  * @return A reference to the stack which was filled.
  */
  Stack& operator=(const Stack &copiedStack);

  /*
  * This is the move assignment which moves the values of a referenced stack to
  * the memory of the left hand stack.
  * Prints a signal when called.
  *
  * @param movedStack A rvalue reference to the moved stack.
  * @return A reference to the stack which was filled.
  */
  Stack& operator=(Stack &&movedStack);

  /*
  * Returns true if the maximum capacity of the stack is reached.
  *
  * @return True if currentSize == maxCapacity.
  */
  bool is_full();

  /*
  * Returns true if there are currently no values in the stack.
  *
  * @return True if the stack is empty. True if currentSize == 0.
  */
  bool is_empty();

  /*
  * If the stack is not full this function pushes the given value on top of the
  * stack. Prints a warning if the stack is full.
  *
  * @param pushedValue The value that is pushed on the stack.
  */
  void push(int pushedValue);

  /*
  * If the stack is not empty this function returns and removes top value of the
  * stack. Prints a warning and returns 0 if the stack is empty.
  *
  * @return The top value of the stack as int. 0 if the stack is empty.
  */
  int pop();

  /*
  * Prints out all values currently on the stack. Prints one single line. All
  * values are divided by a single space.
  */
  void show() const;

  /*
  * Returns the maximum capacity of the stack.
  *
  * @return The maximum capacity as int.
  */
  int capacity() const;

  /*
  * Returns the stack's current size.
  *
  * @return The current size as int.
  */
  int length() const;

};
#endif
