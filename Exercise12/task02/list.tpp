// Implements the class defined in the list.hpp header. Look there for method desciptions.

template< typename T >
List<T>::List(){
  this->first = nullptr;
  this->last = nullptr;
};

template< typename T >
List<T>::~List(){
  this->clear();
};

template< typename T >
void List<T>::add_front(T value){
  Node<T>* added_node = new Node<T>(value);
  // Adds the element at the front and ...
  if(this->isEmpty()){
    this->first = added_node;
    this->last = added_node;
  } else {
    added_node->next = this->first;
    this->first->previous = added_node;
    this->first = added_node;
  }
  // attaches past_the_end_node to the list's end.
  this->past_the_end_node.previous = this->last;
  this->last->next = &(this->past_the_end_node);
};

template< typename T >
void  List<T>::add(T value){
  Node<T>* added_node = new Node<T>(value);
  // Adds the element at the back and ...
  if(this->isEmpty()){
    this->first = added_node;
    this->last = added_node;
  } else {
    added_node->previous = this->last;
    this->last->next = added_node;
    this->last = added_node;
  }
  // attaches past_the_end_node to the list's end.
  this->past_the_end_node.previous = this->last;
  this->last->next = &(this->past_the_end_node);
};

template< typename T >
T List<T>::remove_front(){
  if(this->isEmpty()) return 0;
  Node<T>* front = this->first;
  if(getSize() == 1){
      this->first = nullptr;
      this->last = nullptr;
  } else {
    this->first = this->first->next;
    this->first->previous = nullptr;
  }
  T content = front->content;
  delete front;
  return content;
};

template< typename T >
T List<T>::remove(){
  if(this->isEmpty()) return 0;
  Node<T>* back = this->last;
  if(getSize() == 1){
      this->first = nullptr;
      this->last = nullptr;
  } else {
    // Reataches the past_the_end_node.
    this->last = this->last->previous;
    this->last->next = &past_the_end_node;
    past_the_end_node.previous = this->last;
  }
  T content = back->content;
  delete back;
  return content;
};

template< typename T >
bool  List<T>::isEmpty(){
  return this->first == nullptr;
};

template< typename T >
bool  List<T>::contains(T value){
  bool found = false;
  // Somehow the find and count algorithms would'nt accept Lambdas.. I dont know why!
  std::for_each(this->begin(), this->end(), [&value, &found](T comparing_value){if( comparing_value == value ) found = true; });
  return found;
};

template< typename T >
void  List<T>::clear(){
  while (!(this->isEmpty())) {
    this->remove();
  }
};

template< typename T >
int   List<T>::getSize(){
  int size = 0;
  std::for_each(this->begin(), this->end(), [&size](T comparing_value){ size++; });
  return size;
};

template< typename T >
ListIterator<T> List<T>::begin() { return ListIterator<T>(this->first); }

template< typename T >
ListIterator<T> List<T>::end() { return ListIterator<T>(&(this->past_the_end_node)); }

/**
 * This operator prints all the lists elements to the given ostream.
 * @returns The ostream.
 */
template< typename T >
std::ostream& operator<<( std::ostream& output, List<T>& list){
  if(list.isEmpty()) {std::cout << "List is empty!" << std::endl;}
  else{
    // Gets from past_the_end_node to the last one
    ListIterator<T> current_iterator = --list.end();
    ListIterator<T> begin_iterator = list.begin();
    // Prints up to the beginning of the list.
    // Why there is no reverse for_each?
    while(true){
      T to = *current_iterator;
      std::cout << to << "\t";
      if(current_iterator == begin_iterator) break;
      --current_iterator;
    }
    std::cout << std::endl;
  }
  return output;
}
