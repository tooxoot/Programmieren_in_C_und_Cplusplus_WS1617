/**
 * The abstract bot class which implements the basic message fowarding.
 */
class Bot {
protected:
  Room* assigned_Room; // The Room in which this bot runs.
  string assigned_name; // The bot's name.
  int bot_id; // the bots id which is >= 0.
  static int bot_count; // the total number of bots.
  int messages_read = 0; // the number of messages the bot has processed/ignored.
  thread process_thread; // the Thread in which the bot's loop is running
public:
  /**
   * Basic constructor with geven Room and name.
   */
  Bot (Room* room, string name);
  /**
   * basic destructor
   */
  virtual ~Bot ();

  /**
   * Starts the bot's loop thread
   */
  void initialize_threads();

  /**
   * The pure virtual method all bots have to implement to process the entered messages.
   * @param line the processed Message.
   */
  virtual void process_line( Message line )=0;

  /**
   * The loop which gets Messages from the assigned Room and processes them.
   */
  void process_loop();
};

#include "bot.cpp"
