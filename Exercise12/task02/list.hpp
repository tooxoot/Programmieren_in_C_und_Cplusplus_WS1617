#ifndef LINKED_LIST
#define LINKED_LIST

#include "collection.hpp"
#include "node.hpp"
#include "ListIterator.hpp"
#include <iostream>
#include <algorithm>

/**
 * Implements a linked list consisting of Nodes storing the list's data.
 */
template< typename T>
class List : Collection<T>{
private:
  Node<T>* first = nullptr; //< A pointer to the front of the list.
  Node<T>* last = nullptr;  //< A pointer to the back of the list.
  Node<T> past_the_end_node;//< An empty Node needed to iterate over the List via iterators.
public:
  // The List's iterator class.
  friend class ListIterator<T>;

  /**
   * Constructor initializing the first and last pointers to nullptr.
   */
  List ();
  /**
   * The destructor clearing the List;
   */
  ~List ();

  /**
   * Adds an element to the front of the list.
   * @param  value The added element.
   */
  void add_front(T value);

  /**
   * Method from base-class Collection
   */
  void  add(T value);

  /**
   * Removes and returns the list's front element.
   * @return The front element.
   */
  T remove_front();

  /**
   * Method from base-class Collection
   */
  T remove();

  /**
   * Method from base-class Collection
   */
  bool  isEmpty();

  /**
   * Method from base-class Collection
   */
  bool  contains(T value);

  /**
   * Method from base-class Collection
   */
  void  clear();

  /**
   * Method from base-class Collection
   */
  int   getSize();

  /**
   * Returns a Listiterator to the first element.
   * @ returns  A Listiterator to the first element
   */
  ListIterator<T> begin();

  /**
   * Returns a ListIterator to the past_the_end_node.
   * @ returns a Listiterator pointing to the past the end element.
   */
  ListIterator<T> end();

  /**
   * This operator prints all the lists elements to the given ostream.
   * @returns The ostream.
   */
  // This was the only compiling version to set << as a friend inside this template.
  template<typename U>
  friend std::ostream& operator<<( std::ostream& output, const List<T> list);
};

#include "list.tpp"
#endif
