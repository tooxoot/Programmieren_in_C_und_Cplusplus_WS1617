#include <type_traits>
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <iterator>
#include <utility>
#include <algorithm>

using namespace std;

/**
* Fills the given Container with all even values from 2 to 64.
* @param container The filled vector/deque or list.
*/
template<class Container>
void fill(Container &container){
  for (int val = 2 ; val <= 64; val += 2) container.push_back(val);
}

/**
* Prints the container's elements to std::cout.
* @param container The printed vector/deque or list.
*/
template<class Container>
void print(Container &container){
  for(int val : container) std::cout << val << " ";
  std::cout << std::endl;
}

/**
* Prints 3 elements from the container to std::cout beginning with element referenced
* by the iterator it.
* @param container The printed vector/deque or list.
* @param it        The iterator pointing to the first printed element.
*/
template<class Container, class iterator>
void printnext3(Container &container, iterator it){
  for(int i = 0; i < 3; i++)
    if(it == container.end()) break;
    else {
      std::cout << *it << " ";
      it++;
    }
  std::cout << std::endl;
}

template<class Container>
/**
 * Finds the first position to insert a certain value into the given container
 * so that it stais in ascending order.
 * @param container The searched vector/deque or list.
 * @param insert_val The value that is serached.
 * @return A std::pair consisting of two iterators. The second points to the position
 *         where the value can be inserted, the first points to the element in
 *         front of this position. Both are equal to container.begin() if no position
 *         other than the first is found.
 */
pair<typename Container::iterator, typename Container::iterator> findposition(Container &container, typename Container::value_type insert_val){
  typename Container::iterator it_current = container.begin();
  typename Container::iterator it_next = container.begin();
  it_next++;
  for(it_current, it_next; it_current != container.end(); it_current++, it_next++ ){
        if(it_next == container.end() && *it_current <= insert_val ) return make_pair(it_current,it_next);
        if(*it_current <= insert_val && *it_next >= insert_val) return make_pair(it_current,it_next);
  }
  return make_pair(container.begin(),container.begin());
}

/**
 * A functor which is used by the deleteodd function to determine the container's
 * odd elements and to calculate the new container size.
 */
template<class Value>
struct deleteodd_functor{
  /**
   * This constructor accepts an int reference which is used to store the new
   * container size.
   */
  deleteodd_functor(int& new_container_size) : size(new_container_size) {}
  /**
   * The operator is used to determine if an element is odd.
   * @return The processed element.
   */
  bool operator()(Value val){
    if( val % 2 == 0 ) return false;
    size--;
    return true;
  }

private:
  int& size; //<< A reference hich is used to store the new container size.
};

/**
* Deletes all odd elements from the given container.
* @param container The vector/deque or list from which all odd elements are removed.
*/
template<class Container>
void deleteodd(Container &container){
  int new_container_size = container.size(); //< Needed for later resizing of the arguments-vector.
  // Question: Is there a remove function which resizes the container by itself?
  remove_if(  container.begin(),
              container.end(),
              deleteodd_functor<typename Container::value_type>(new_container_size)
            );
  container.resize(new_container_size);
}


int main(int argc, char const *argv[]) {
  // Initializes the different containers.
  std::vector<long> vector_long;
  std::deque<long> deque_long;
  std::list<long> list_long;

  // Fills them
  fill(vector_long);
  fill(deque_long);
  fill(list_long);

  // Iterators to the first element
  vector<long>::iterator vector_it = vector_long.begin();
  deque<long>::iterator deque_it = deque_long.begin();
  list<long>::iterator list_it = list_long.begin();

  // Advaces the iterators to the third element by using as few commands as possible.
  vector_it += 2;
  deque_it += 2;
  list_it++;
  list_it++;

  // Should print out '4\n' for each container.
  std::cout << *vector_it << std::endl;
  std::cout << *deque_it << std::endl;
  std::cout << *list_it << std::endl;

  // Finds the positions where 31 can be inserted.
  pair<vector<long>::iterator, vector<long>::iterator> vector_found = findposition(vector_long, 31);
  pair<deque<long>::iterator, deque<long>::iterator> deque_found = findposition(deque_long, 31);
  pair<list<long>::iterator, list<long>::iterator> list_found = findposition(list_long, 31);

  // Inserts 31 on each position. The returned iterator is only used in FIX_B!
  vector<long>::iterator vector_insert_it = vector_long.insert(vector_found.second, 31);
  deque<long>::iterator deque_insert_it = deque_long.insert(deque_found.second, 31);
  list<long>::iterator list_insert_it = list_long.insert(list_found.second, 31);

  // Without fix the decremented second element from the findposition pair is used.
  vector<long>::iterator vector_print_it = --vector_found.second;
  deque<long>::iterator deque_print_it = --deque_found.second;
  list<long>::iterator list_print_it = --list_found.second;

  #ifdef FIX_A
    /*
    To find the element in front of the inserted position we have to find the first
    31 in the vector and deque. These iterators are the used for the printnext3
    function.
    */
    vector_print_it = find_if(vector_long.begin(), vector_long.end(), [](long val){ return val == 31; });
    deque_print_it = find_if(deque_long.begin(), deque_long.end(), [](long val){ return val == 31; });
  #endif
  #ifdef FIX_B
    /*
    To use the return value of the insert method, wich points to the first of the
    inserted elements, we simply use it for the printnext3 function.
     */
    vector_print_it = vector_insert_it;
    deque_print_it = deque_insert_it;
  #endif

  // Should ideally print out '31 32 34' for each container.
  printnext3(vector_long, vector_print_it);
  printnext3(deque_long, deque_print_it);
  printnext3(list_long, list_print_it);

  // Prints out all elements from each container.
  print(vector_long);
  print(deque_long);
  print(list_long);

  // deletes all odd elements from each container.
  deleteodd(vector_long);
  deleteodd(deque_long);
  deleteodd(list_long);

  // Prints out all elements from each container.
  print(vector_long);
  print(deque_long);
  print(list_long);

  return 0;
}
