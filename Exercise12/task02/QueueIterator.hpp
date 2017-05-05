#ifndef QUEUEITERATOR
#define QUEUEITERATOR

/**
 * Implements an iterator for the Queue class by inheriting from the ListIterator class.
 * This is a only deviation from the given class diagramm! But it is needed to
 * iterate over the queue qithout changing the public iterfaces from List and Queue!
 */
template< typename T >
class QueueIterator : public ListIterator<T>, public std::iterator<std::forward_iterator_tag, T>{
public:
  /**
   * Constructor which sets the current node pointer to a given one.
   * Basically useless with the class diagramm changes I made.
   */
  QueueIterator (Node<T>* node) : ListIterator<T>(node) {};

  // The destructor
  virtual ~QueueIterator () {};

  /**
   * Compares two iterators by evaluating if they are pointing to the same node.
   * Uses the base classes == operator method.
   * @returns True if the two Iterators point to the exact same node.
   */
  bool operator==(const QueueIterator<T>& qi) const { return ListIterator<T>::operator==(qi); }

  /**
   * Compares two iterators by evaluating if they are not pointing to the same node.
   * Uses the base classes != operator method.
   * @returns True if the two Iterators do not point to the exact same node.
   */
  bool operator!=(const QueueIterator<T>& qi) const { return ListIterator<T>::operator!=(qi); }

  /**
   * Returns the value of this iterator by dereferencing its node.
   * Uses the base classes * operator method.
   * @returns The iterator's value.
   */
  T operator*() const { return ListIterator<T>::operator*(); };

  /**
   * Increments the Iterator by jumping from the current node to the next one.
   * Uses the base classes ++ operator method.
   * @returns This iterator.
   */
  QueueIterator<T>& operator++() { ListIterator<T>::operator++(); return *this; }

  // Deletes the base-classes -- operator;
  QueueIterator<T>& operator--() = delete;
};

#endif
