/**
 * This Bot just repeats all Messages not containing an '?'.
 */
class Bot_Echo : public Bot {
public:
  //See Bot
  Bot_Echo (Room* room, string name);
  ~Bot_Echo ();

  /**
   * Repeats all incoming messages not containing a '?' appending a '?'.
   */
  void process_line(Message line);

};

#include "bot_echo.cpp"
