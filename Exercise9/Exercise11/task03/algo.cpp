#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

/**
 * Programm accepts a command (listed below) and a variable number of long arguments.
 */
int main(int argc, char *argv[]) {
  string command = argv[1];
  vector<long> arguments;
  // Push all long-arguments from console input to arguments-vector.
  for_each( &argv[2],
            &argv[argc],
            [&arguments](char* arg){
              // To overcome issues with accidently given strings.
              try{ arguments.push_back( stol(arg) ); } catch(...){}
            }
          );

  // Switch command
  if( command == "countodd" ){
    // Counts all odd arguments...
    int number_of_odd_elements = count_if(  arguments.begin(),
                                            arguments.end(),
                                            [](long arg){ return arg % 2 != 0; }
                                          );
    // and prints out the number.
    std::cout << number_of_odd_elements << std::endl;
  } else if ( command == "hasnegative" ){
    // Counts all negative arguments...
    int number_of_negative_elements = count_if( arguments.begin(),
                                                arguments.end(),
                                                [](long arg){ return arg < 0; }
                                               );
    // and prints out 'Yes' if there is at least one. Else Prints out 'No'
    if ( number_of_negative_elements > 0) std::cout << "Yes" << std::endl;
    else std::cout << "No" << std::endl;
  } else if ( command == "inc" ){
    // Adds 1 to all of arguments' elements.
    transform(arguments.begin(),
              arguments.end(),
              arguments.begin(), //< Put the first transformed element here.
              [](long arg){ return arg + 1; }
              );
    // Prints out all arguments seperated by a space;
    for_each( arguments.begin(),
              arguments.end(),
              [](long arg){ std::cout << arg << " ";}
            );
    std::cout << std::endl;
  } else if ( command == "sum" ){
    long sum = 0;
    // Calculates the sum of all arguments.
    for_each( arguments.begin(),
              arguments.end(),
              [&sum](long arg){ sum += arg; }
            );

    /** equivalent solution using the header <numeric>! */
    // long sum = accumulate(  arguments.begin(),
    //                         arguments.end(),
    //                         0 //< Initial value of the returned sum.
    //         );

    //Prints out the sum.
    std::cout << sum << std::endl;
  } else if ( command == "deleteodd" ){
    // Removes all odd elements from the arguments-vector.
    int new_vector_size = arguments.size(); //< Needed for later resizing of the arguments-vector.
    remove_if(  arguments.begin(),
                arguments.end(),
                [&new_vector_size](long arg){
                  if( arg % 2 == 0 ) return false;
                  new_vector_size--;
                  return true;
                }
              );
    // Resizes the vector to fit the even elements.
    arguments.resize(new_vector_size);
    // Prints out all arguments seperated by a space;
    for_each( arguments.begin(),
              arguments.end(),
              [](long arg){ std::cout << arg << " ";}
            );
    std::cout << std::endl;
  } else { // default
    std::cout << "Invalid command: " << command << std::endl;
  }
  return 0;
}
