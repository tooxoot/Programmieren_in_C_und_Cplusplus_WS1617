/**
 * This Bot determines if given Parameter are prime numbers
 */
class Bot_Prime : public Bot {
public:
  //see Bot
  Bot_Prime (Room* room, string name);
  ~Bot_Prime ();
  thread* temp_thread; // See others

  /**
   * When the command isprime arg1 arg2 ... is entered this Bot will print out if
   * the arguments are prime numbers
   * @param line [description]
   */
  void process_line(Message line);

  /**
   * The thread Method to start all prime calculations.
   */
  void start_prime_thread(string delayed_content);

  /**
   * Determines if a number is prime.
   * @param  candidate The Number which is checked
   * @return           True if the number is prime
   */
  bool is_prime(int candidate);
};

#include "bot_prime.cpp"
