#ifndef NODE
#define NODE

template< typename T >
class Node {
public:
  T content;
  Node<T>* previous;
  Node<T>* next;
  Node (T content = T(), Node* next = nullptr, Node* previous = nullptr){
    this->content = content;
    this->previous = previous;
    this->next = next;
  };
  ~Node (){};
  bool operator==(const Node<T>& node){ return this->content == node.content; }
};

#endif
