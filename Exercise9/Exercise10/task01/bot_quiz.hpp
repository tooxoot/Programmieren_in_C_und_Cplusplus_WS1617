/**
 * This Bot plays a Quiz from a given File
 */
class Bot_Quiz : public Bot {
public:
  bool is_quizing = false; // Saves if there is currently running quiz
  deque<string> questions; // Holds all the questions
  deque<string> answers; // Holds all the answers
  //see Bot
  Bot_Quiz (Room* room, string name);
  ~Bot_Quiz ();

  /**
   * When the command startquiz <filename is entered a new quiz is started from given file.
   */
  void process_line(Message line);

  /**
   * Initializes the quiz from a given file
   * @param filename the file's path.
   */
  void initialize_quiz(string filename);

  /**
   * Prompts the quizes next question.
   */
  void next_question();
};

#include "bot_quiz.cpp"
