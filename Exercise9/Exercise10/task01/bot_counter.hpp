/**
 * This Bot counts up to 3 seconds
 */
class Bot_Counter : public Bot {
public:
  thread* temp_thread; // just here so that the counting thread is not terminated. Are there better methods?
  //see Bot
  Bot_Counter (Room* room, string name);
  ~Bot_Counter ();

  /**
   * When the command startcounter is entered this Bot starts counting up to three seconds.
   */
  void process_line(Message line);

  /**
   * The thread method to count to 3.
   */
  void start_counter_thread();
};

#include "bot_counter.cpp"
