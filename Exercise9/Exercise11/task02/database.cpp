#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Typedef for the key.
typedef string key;
// Typedef for the value.
typedef vector<int> value;

/**
 * Defines a map of key-value pairs where the key is a string and its value is a
 * vector<int>.
 */
typedef struct{ vector<key> keys; vector<value> values; } map;

static map input_map; //<< This map stores the input lines as keys and their line numbers as values;
static int line_number = 1; //<< The ascending line number which is addes;

/**
 * Accepts a string as input and adds the current line number to the input_map.
 * Either a new key-value pair is added or the currrent line number is added to
 * an existing key's value.
 * @param line The line that was entered.
 */
void add_line(string line){
  // Searches for an existing key.
  for (int i = 0; i < input_map.keys.size(); i++)
    if(input_map.keys[i] == line){
      input_map.values[i].push_back(line_number);
      return;
    }
  // Adds a new key-value pair.
  input_map.keys.push_back(line);
  std::vector<int> val;
  input_map.values.push_back(val);
  input_map.values.back().push_back(line_number);
}

/**
 * Prints out all line numbers from the value-vector assigned to the given key line.
 * Prints out 'Not found' if the given key does not exist in the input_map.
 * @param line The line that was enterd.
 */
void print_values(string line){
  for (int i = 0; i < input_map.keys.size(); i++)
    if( input_map.keys[i] == line){
      for(int val : input_map.values[i])
          std::cout << val << " ";
      std::cout << std::endl;
      return;
    }
  std::cout << "Not found" << std::endl;
}

/**
 * Prints out all key-value pairs from input_map.
 * For debugging purposes only.
 */
void debug_printer(){
  std::cout << "input_map:" << std::endl;
  for (int i = 0; i < input_map.keys.size(); i++) {
    std::cout << "\t" << input_map.keys[i] << " -> ";
    for(int val : input_map.values[i]) std::cout << val << " ";
    std::cout << std::endl;
  }
}

/**
 * Adds key-value pairs to the input_map until "." is entered.
 * Then prints out all elements from the value-vector of a given key, until "."
 * is entered.
 */
int main() {
  string input;
  while(getline(cin, input))
    if(input == ".") break;
    else {
      add_line(input);
      line_number++;
    }

  while(getline(cin, input))
    if(input == ".") break;
    else print_values(input);

  return 0;
}
