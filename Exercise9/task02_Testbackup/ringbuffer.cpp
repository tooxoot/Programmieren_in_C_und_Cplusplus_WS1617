// Include definition of class StopWatch in ringbuffer.hpp.


/*
* This is the source file to header file ringbuffer.hpp containing the RingBuffer
* class.Please look at the header for method descriptions.
*/

//As you can see these methods handle the range 'overflow' inside the buffer's array.
template <class T, int Maximum_Capacity>
int RingBuffer<T,Maximum_Capacity>::position_increase(int position) const{
  if(position + 1 >= max_capacity) return 0;
  return position + 1;
};

template <class T, int Maximum_Capacity>
int RingBuffer<T,Maximum_Capacity>::position_decrease(int position) const{
  if(position - 1 < 0) return max_capacity - 1;
  return position - 1;
};

template <class T, int Maximum_Capacity>
RingBuffer<T,Maximum_Capacity>::RingBuffer (){
  count = 0;
  max_capacity = Maximum_Capacity;
  position_front = 0;
  position_back = 0;
  for (int i = 0; i < max_capacity; i++) elements[i] = NULL;
};

template <class T, int Maximum_Capacity>
RingBuffer<T,Maximum_Capacity>::~RingBuffer (){
  for (int i = 0; i < max_capacity; i++) elements[i] = NULL;
};


template <class T, int Maximum_Capacity>
void RingBuffer<T,Maximum_Capacity>::push_front(const T& val){
  if(full()) return;
  // Here you see that position_front does not point to the front element but to the space ahead of it.
  elements[position_front] = &val;
  position_front = position_increase(position_front);
  count++;
};

template <class T, int Maximum_Capacity>
T RingBuffer<T,Maximum_Capacity>::pop_front(){
  if(empty()) throw std::range_error("pop_front on empty buffer");
  const T *return_val = elements[position_decrease(position_front)];
  elements[position_decrease(position_front)] = NULL;
  position_front = position_decrease(position_front);
  count--;
  return *return_val;
};

template <class T, int Maximum_Capacity>
void RingBuffer<T,Maximum_Capacity>::push_back(const T& val){
  if(full()) return;
  elements[position_decrease(position_back)] = &val;
  position_back = position_decrease(position_back);
  count++;
};

//TODO Exceptionstd::cout << rb.pop_back() << std::endl;
template <class T, int Maximum_Capacity>
T RingBuffer<T,Maximum_Capacity>::pop_back(){
  if(empty()) throw std::range_error("pop_back on empty buffer");
  const T *return_val = elements[position_back];
  elements[position_back] = NULL;
  position_back = position_increase(position_back);
  count--;
  return *return_val;
};

template <class T, int Maximum_Capacity>
bool RingBuffer<T,Maximum_Capacity>::empty() const{
  return size() == 0;
};

template <class T, int Maximum_Capacity>
bool RingBuffer<T,Maximum_Capacity>::full() const{
  return size() == max_capacity;
};

template <class T, int Maximum_Capacity>
void RingBuffer<T,Maximum_Capacity>::print() const{
  // Debug printout
  #ifdef DEBUG
  // std::cout << "count = " << count << std::endl;
  // std::cout << "max_capacity = " << max_capacity << std::endl;
  // std::cout << "position_front = " << position_front << std::endl;
  // std::cout << "position_back = " << position_back << std::endl;
  for (int i = 0; i < max_capacity; i++) {
    if(elements[i]==0) std::cout << "@0\t";
    else std::cout << *(elements[i]) << "\t";
  }
  std::cout << "\n";
  #endif

  if (empty()) {
    std::cout << "Buffer is empty" << std::endl;
    return;
  }

  std::cout << "Content of buffer:";
  int position_temp = position_decrease(position_front);
  for (int i = 0; i < size(); i++) {
    std::cout << "\t" << *(elements[position_temp]);
    position_temp = position_decrease(position_temp);
  }
  std::cout << std::endl;
};

//in this case it's trivial!
template <class T, int Maximum_Capacity>
int RingBuffer<T,Maximum_Capacity>::size() const{
  return count;
}
