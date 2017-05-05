// Implements the class defined in the list.hpp header. Look there for method desciptions.

template< typename T >
Queue<T>::Queue(){
  this->list = new List<T>();
};

template< typename T >
Queue<T>::~Queue (){
  delete list;
};

template< typename T >
void  Queue<T>::add(T value){
  list->add(value);
};

template< typename T >
T     Queue<T>::remove(){
  return list->remove_front();
};

template< typename T >
bool  Queue<T>::isEmpty(){
  return list->isEmpty();
};

template< typename T >
bool  Queue<T>::contains(T value){
  return list->contains(value);
};

template< typename T >
void  Queue<T>::clear(){
  list->clear();
};

template< typename T >
int   Queue<T>::getSize() {
  return list->getSize();
};

template< typename T >
QueueIterator<T> Queue<T>::begin() {
  ListIterator<T> li = list->begin();
  return static_cast<QueueIterator<T>&>( li );
}

template< typename T >
QueueIterator<T> Queue<T>::end() {
  ListIterator<T> li = list->end();
  return static_cast<QueueIterator<T>&>( li );
}

template< typename T >
std::ostream& operator<<( std::ostream& output, Queue<T>& queue){
  if( queue.isEmpty() ) { std::cout << "Queue is empty!" << std::endl; }
  else{
    std::for_each(queue.begin(), queue.end(), [](T value){ std::cout << value << "\t";} );
    std::cout << std::endl;
  }
  return output;
}
