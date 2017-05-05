#include <vector>
#include <stdexcept>

/**
 * Implements a double sided queue.
 */
template <typename T, int Maximum_Capacity>
class RingBuffer {
private:
  int max_capacity;   /**< The maximum number of elements.*/
  int position_front; /**< The index of the element at the front of the queue. Note that the front element will be at position_front-1 */
  int position_back;  /**< The index of the element at the end of the queue.*/
  const T *elements[Maximum_Capacity]; /**< An array of pointers to queue's elements. */

  /**
   * Handles the increase of a position index from the queue's array. (e.g. position_front/_back)
   * Note that the index itself is not increased directly but the increased index is returned.
   * Therefore this method can also be used to cycle through the queue.
   * Example: Instead of 'position_front++' use : 'position_front = position_increase(position_front)'
   * @param  position The index wich will be increased.
   * @return          The increased index.
   */
  int position_increase(const int position) const;

  /**
   * Handles the decrease of a position index from the queue's array. (e.g. position_front/_back)
   * Note that the index itself is not decreased directly but the decreased index is returned.
   * Therefore this method can also be used to cycle through the queue.
   * Example: Instead of 'position_front--' use : 'position_front = position_decrease(position_front)'
   * @param  position The index wich will be decreased.
   * @return          The decreased index.
   */
  int position_decrease(const int position) const;
public:
  /**
   * An ordinary constructor. The maximum capacity is automaticly set to Maximum_Capacity
   */
  RingBuffer ();

  /**
   * An ordinary destructor.
   */
  ~RingBuffer ();

  /**
   * Pushes an element to the front of the buffer. The element will be dropped silently
   * if the buffer is full.
   * @param  val The pushed element
   */
  void push_front(const T& val);

  /**
   * Removes and returnes the front element of the buffer. Throws exception (std::range_error)
   * if the buffer is empty.
   * @return The removed front element.
   */
  T pop_front();

  /**
   * Pushes an element to the back of the buffer. The element will be dropped silently
   * if the buffer is full.
   * @param  val The pushed element
   */
  void push_back(const T& val);

  /**
   * Removes and returnes the back element of the buffer. Throws exception (std::range_error)
   * if the buffer is empty.
   * @return The removed back element.
   */
  T pop_back();

  /**
   * Checks if the buffer is empty.
   * @return True if the buffer does not contain any elements. Else returns false.
   */
  bool empty() const;

  /**
   * Checks if the buffer is full.
   * @return True if the maximum capacity is reached. Else returns false.
   */
  bool full() const;

  /**
   * Prints out a '\t' seperated list of the buffer's elements.
   * States if the buffer is empty.
   */
  void print() const;

  /**
   * Retunrs the current size of the buffer.
   * @return The number of elements in the buffer.
   */
  int size() const;
};

#include "ringbuffer2.cpp"
