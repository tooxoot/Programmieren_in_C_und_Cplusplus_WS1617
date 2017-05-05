/**
 * This Bot Repeats a certain Message when the delayed command is entered
 */
class Bot_Delay : public Bot {
public:
  thread* temp_thread; // This thread* is just here so that the counting thread is not terminated.

  //see Bot
  Bot_Delay (Room* room, string name);
  ~Bot_Delay ();

  /**
   * If the command delayed <text> is entered the text is repeated after 2 seconds.
   */
  void process_line(Message line);

  /**
   * The thread method to enter the text again after 2 seconds. 
   */
  void start_delay_thread(string delayed_content);
};

#include "bot_delay.cpp"
