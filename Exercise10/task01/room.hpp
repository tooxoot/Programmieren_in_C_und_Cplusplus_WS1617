// These Makros define the different bot types
#define ECHO "echo"
#define COUNTER "counter"
#define DELAY "delay"
#define PRIME "prime"
#define QUIZ "quiz"

/**
 * These Integers indicate different types of messages used in the Message struct.
 * USER_INPUT: Stands for a normal message sent by the User.
 * BOT_COMMAND: Indicates a bot creation command.
 * EXIT: Is set when the exit command was entered.
 */
enum MessageTypes { USER_INPUT = -1, BOT_COMMAND = -2, EXIT = -3};

/**
 * This structure defines the Data for a chat-message.
 */
struct Message {
  string content = ""; // The printet content of the Message
  string botname = ""; // If this message was sent by a bot, its name is stored here.
  int type_id = -99;   // Either one of the above MessageTypes or (if the message was send by a bot) the bot's id.
};

/**
 * A class representing a simulated chatroom populated by different Bots.
 * The Idea behind it is to have two different Lists of Messages: received_messages
 * and accepted_messages. Every Message entered in the chatroom via enter_message
 * is first put into the received_messages list from which it is then read and
 * processed. All Messages which were processed are then stored in the accepted_messages
 * list from where they can be read via get_message.
 */
class Room {
private:
  deque<Message>   received_messages; // All messages received from the User or one of the Bots are stored here.
  vector<Message>  accepted_messages; // All received_messages which were processes by the Chat-room are stored here.
  mutex queue_lock; // This lock keeps received_messages deque safe from simultanious access.
  bool exit_flag = false; // Indicates that the exit command was received.
  thread process_thread; // The thread that processes all received messages.
  thread input_thread; // The thread that gets the users input.
public:
  /**
   * Just a constructor;
   */
  Room ();

  /**
   * Just a destructor;
   */
  virtual ~Room ();

  /**
   * Initializes the two thread members.
   */
  void initialize_threads();

  /**
   * This loop processes all Messages currently in received_messages and empties the queue.
   */
  void process_loop();

  /**
   * This loop receives user input, builds a Message from it and enters it in the chatroom.
   */
  void input_loop();

  /**
   * This Method processes the different Message types. It also removes them from
   * the received_messages list to put them on the accepted_messages list.
   * @param line The current processed Message.
   */
  void process_line(Message line);

  /**
   * Creates bot from a given parameter sring.
   * @param parameters A string in form of <bot_type>,<bot_name>
   */
  void create_Bot(string parameters);

  /**
   * Returns the number of accepted messages which is equal to accepted_messages.size().
   * @return The number of accepted messages
   */
  int get_messagecount() const;

  /**
   * Gets a specific message from the list af accepted messages.
   * @param  n The position of the message in the list.
   * @return   The message which is equal to accepted_messages[n].
   */
  Message get_message(int n) const;

  // Pushes message to into received_messages. Returning the number of received but unaccepted messages.
  /**
   * Pushes message to onto the list of received messages. Returning the total
   * number of received but unaccepted messages.
   * @param  message The message which is entered to the chat.
   * @return         The number of accepted messages which is equal to accepted_messages.size().
   */
  int enter_message( Message message );

  /**
   * Sets the exit_flag which is used to control the different threads.
   */
  void set_exitflag();

  /**
   * Returns if the exit_flag was set.
   * @return True if the exit_flag was set.
   */
  bool get_exitflag();
};

// Unfortunately I Had to include all the files here beacause of some ugly cross referencing. 
#include "bot.hpp"
#include "bot_echo.hpp"
#include "bot_counter.hpp"
#include "bot_delay.hpp"
#include "bot_prime.hpp"
#include "bot_quiz.hpp"
#include "room.cpp"
