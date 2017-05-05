#ifndef QUEUE
#define QUEUE

#include "list.hpp"
#include "QueueIterator.hpp"

/**
 * Implements a queue using the Collection class and an underlying List.
 */
template<typename T>
class Queue : Collection<T> {
private:
  List<T>* list; //< A pointer to the underlying List which holds and manages the Queue's elements.
public:
  /**
   * Constructor wchich initializes the underlying List.
   */
  Queue ();

  // The destructor
  ~Queue ();

  /**
   * Method from base-class Collection
   */
  void  add(T value);

  /**
   * Removes and returns the Queue's front element. IS NOT EQUIVALENT TO THE BASE-
   * CLASSE'S remove() METHOD!
   * @return The front element.
   */
  T     remove();

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
   * Returns a QueueIterator by casting the begin() iterator from the underlying list.
   * @returns  A QueueIterator to the first element
   */
  QueueIterator<T> begin();

  /**
   * Returns a QueueIterator by casting the end() iterator from the underlying list.
   * @returns A QueueIterator pointing to the past the end element.
   */
  QueueIterator<T> end();

  /**
   * This operator prints all the queue's elements to the given ostream.
   * @returns The ostream.
   */
  template< typename U >
  friend std::ostream& operator<<( std::ostream& output, Queue<T>& queue);

};

#include "queue.tpp"
#endif
