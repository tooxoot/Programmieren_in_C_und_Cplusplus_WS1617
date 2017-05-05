#include <iostream>
#include <cstring>
// Include definition of class Stack in stack.hpp.
#include "stack.hpp"

/*
* This is the source file to header file stack.hpp containing the Stack class.
* Please look at the header for Method descriptions.
*/

void Stack::copy(const Stack &copiedStack){
  memcpy( &(this->maximumCapacity), &(copiedStack.maximumCapacity), sizeof(copiedStack.maximumCapacity) );
  memcpy( &(this->currentSize), &(copiedStack.currentSize), sizeof(copiedStack.currentSize) );
  this->arr = new int[this->maximumCapacity];
  memcpy( this->arr, copiedStack.arr, this->maximumCapacity * sizeof(int) );
}

/* As I mentioned in the header file this method should provide a functionality
* similar to the copy method above to shorten the now redundant code provided in
* the move assignment and operator.
* I failed to work out how this could work and would like to see a function head
* and the corresponding call in e.g. the move operator.
*/
// void Stack::move(Stack &&s){
//   this->maximumCapacity = std::move(s->cap);
//   this->currentSize = std::move(s->currentSize);
//   this->arr = new int[this->maximumCapacity];
//   for (int i = 0; i < this->maximumCapacity; i++) {
//     this->arr[i] = std::move(s->arr[i]);
//   }
//   s->currentSize = 0;
// }


Stack::Stack() : Stack(10){}

Stack::Stack(int maxCapacity){
  this->maximumCapacity = maxCapacity;
  this->currentSize = 0;
  this->arr = new int[this->maximumCapacity];
  std::cout << "Ctor: I am allocating space for " << this->maximumCapacity << " integers";
  std::cout << std::endl;
}

Stack::Stack(const Stack &copiedStack){
  copy(copiedStack);
  std::cout << "Cctor called" << std::endl;
}

Stack::Stack(Stack &&movedStack){
  this->maximumCapacity = std::move(movedStack.maximumCapacity);
  this->currentSize = std::move(movedStack.currentSize);
  this->arr = new int[this->maximumCapacity];
  for (int i = 0; i < this->maximumCapacity; i++) {
    this->arr[i] = std::move(movedStack.arr[i]);
  }
  movedStack.currentSize = 0;
  movedStack.maximumCapacity = 0;
  std::cout << "Mctor called" << std::endl;
}

  //destructor
Stack::~Stack(){
  delete[] this->arr;
  std::cout << "Dtor: I am deallocating a stack of " << this->maximumCapacity;
  std::cout << " integers filled with " << this->currentSize << " values.";
  std::cout << std::endl;
}

Stack& Stack::operator=(const Stack &copiedStack){
  copy(copiedStack);
  std::cout << "Cop= called" << std::endl;
}

Stack& Stack::operator=(Stack &&movedStack){
  this->maximumCapacity = std::move(movedStack.maximumCapacity);
  this->currentSize = std::move(movedStack.currentSize);
  this->arr = new int[this->maximumCapacity];
  for (int i = 0; i < this->maximumCapacity; i++) {
    this->arr[i] = std::move(movedStack.arr[i]);
  }
  movedStack.currentSize = 0;
  movedStack.maximumCapacity = 0;
  std::cout << "Mop= called" << std::endl;
}

bool Stack::is_full(){
  return (this->maximumCapacity == this->currentSize);
}

bool Stack::is_empty(){
  return this->currentSize == 0;
}

void Stack::push(int pushedValue){
  if(this->is_full()) {
    std::cout << "The stack is full" << std::endl;
    return;
  }
  this->arr[this->currentSize] = pushedValue;
  this->currentSize++;
}

int Stack::pop(){
  if (this->is_empty()){
    std::cout << "The stack is empty" << std::endl;
    return 0;
  }
  this->currentSize--;
  return this->arr[this->currentSize];
}

void Stack::show() const{
  for (int i = 0; i < this->currentSize; i++) {
    std::cout << this->arr[i];
    if(i != this->currentSize - 1) std::cout << " ";
  }
  std::cout << std::endl;
}

int Stack::capacity() const{
  return this->maximumCapacity;
}

int Stack::length() const{
  return this->currentSize;
}
