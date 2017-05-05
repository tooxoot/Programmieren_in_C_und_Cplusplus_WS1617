#ifndef LISTITERATOR
#define LISTITERATOR
#include <iterator>

/**
 * Implements an iterator for the List class.
 */
template< typename T >
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
private:
  Node<T>* node; //< The current node.
  /**
   * Private method to get the current node pointer. Importend to compare two Itterators.
   * @returns The node pointer.
   */
  Node<T>* get_node() const { return node; }
public:
  /**
   * Constructor which sets the current node pointer to a given one.
   */
  ListIterator (Node<T>* node){ this->node = node; };
  //destructor
  ~ListIterator () {
    // delete node; //?
  };

  /**
   * Compares two iterators by evaluating if they are pointing to the same node.
   * @returns True if the two Iterators point to the exact same node.
   */
  bool operator==(const ListIterator<T>& li) const { return this->node == li.get_node(); }

  /**
   * Compares two iterators by evaluating if they are not pointing to the same node.
   * @returns True if the two Iterators do not point to the exact same node.
   */
  bool operator!=(const ListIterator<T>& li) const { return !(this->node == li.get_node()); }

  /**
   * Returns the value of this iterator by dereferencing its node.
   * @returns The iterator's value.
   */
  T operator*() const { return this->node->content; };

  /**
   * Increments the Iterator by jumping from the current node to the next one.
   * @returns This iterator.
   */
  ListIterator<T>& operator++() { this->node = this->node->next; return *this; }

  /**
   * Decrements the Iterator by jumping from the current node to the previous one.
   * @returns This iterator.
   */
  ListIterator<T>& operator--() { this->node = this->node->previous; return *this; }
};

#endif
