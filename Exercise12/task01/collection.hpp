#ifndef COLLECTION_TEMPLATE
#define COLLECTION_TEMPLATE


/**
 * Implements the pure abstract class for a basic collection.
 */
template< typename T >
class Collection {
public:
  
  /**
   * Adds an element of specific value to the collection.
   * @param  value The added element.
   */
  virtual void  add(T value) = 0;

  /**
   * Removes and returns the back element of this collection.
   * @return The back element.
   */
  virtual T     remove() = 0;

  /**
   * Checks if this collection is empty.
   * @return True if there are no elements in this collection. False otherwise.
   */
  virtual bool  isEmpty() = 0;

  /**
   * Checks if this collection contains an element of specific value.
   * @param  value The value of the searched element.
   * @return       Returns true if this collection contains an element equal to the given one.
   */
  virtual bool  contains(T value) = 0;

  /**
   * Empties the collection by removing all elements.
   */
  virtual void  clear() = 0;

  /**
   * Returns the number of elements currently in the collection.
   * @return The Number of elements.
   */
  virtual int   getSize() = 0;
};

#endif
