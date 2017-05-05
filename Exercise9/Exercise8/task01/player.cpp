
// Enum containing the different AI modes.
enum Mode {RANDOM = 0, MINMAX = 1};

/**
 * Promts the player for a given argument. The Player is then able to enter an int.
 * @param  arg    The Name of the prompt.
 * @param  minVal The minimum value the player has to enter.
 * @param  maxVal The maximum value the player can enter.
 * @return        Returns the entered int
 */
int promptFor(std::string arg, int minVal, int maxVal){
  int returnVal;
  std::string input;
  while(true){
    //Promts for argument
    std::cout << arg;
    std::cin >> input;
    //Checks if the input is valid
    try {
      returnVal = std::stoi(input);
      if(input.length() > 1 || returnVal < minVal || returnVal > maxVal) throw -1;
      return returnVal;
    }catch(...){
      std::cout << "Ivalid input! Please insert Number from " << minVal << " up to " << maxVal << std::endl;
    }
  }
}

/**
 * This class represents a player with its base functionalities.
 */
class Player {
private:
  int number = 0; /**< The Players number (1/2) */
public:
  /** Initializes the player with given number */
  Player (int num){ this->number = num; }

  /**
   * This function is called when the player has to make his turn.
   * @param gb The current board.
   */
  virtual void play(Board& gb) {};
  /** Returns the player's number */
  int getNumber() const { return number; }
};

/**
 * This class represents a human player.
 */
class Human : public Player{
private:
  /** The promt above is a friend */
  friend int promptFor(std::string arg,int  minVal, int maxVal);
public:
  /** Constructor as in Player */
  Human (int num) : Player(num){}

  /**
   * Prompts the player for a row and column. If the entered position is free the
   * the Player number is inserted to the board.
   * @param gb The current board.
   */
  void play(Board& gb) {
    while(true){
      std::cout << "Player " << this->getNumber() << "'s turn" << std::endl;
      int row = promptFor("Select a row: ", 1, 3) - 1;
      int col = promptFor("Select a column: ", 1, 3) - 1;
      if(gb.insert(this->getNumber(), row, col)) return;
      std::cout << "Position is already occupied. Enter new one!" << std::endl;
    }
  }
};

/**
 * This class represents an AI-player
 */
class Computer : public Player{
private:
  Mode mode; /**< The AI mode (Random / MinMax) */
  ComputationBoard *cb; /**< The board representation used to calculate the MinMax Ai. */

  /**
   * Computes the RandomAI's move
   * @param gb The board
   */
  void playRandom(Board& gb){
    while(!gb.insert(this->getNumber(), rand()%3, rand()%3));
  }

  /**
   * Computes the MinMaxAI's move
   * @param gb The current board
   */
  void playMinMax(Board& gb){
    //Checks which move the human player has made and writes it to the ComputationBoard.
    for (int i = 0; i < cb->branches.size(); i++)
      if (cb->branches[i] == gb){
        cb = &(cb->branches[i]);
      }

    int minVal = cb->branches[0].val;
    int choice = 0;
    //This Loop calculates the best possible move
    for (int i = 0; i < cb->branches.size(); i++)
      if(cb->branches[i].val >= minVal){
        bool valid = true;
        /**
         *  Something in the ComputationBoard algorithm seems to be wrong because
         *  here I have to check if the Human Player could take a winning move in
         *  the his next turn.
         */
        for (int j = 0; j < cb->branches[i].branches.size(); j++)
          if (cb->branches[i].branches[j].getWinner() == -10){
            valid = false;
          }
        if(valid){
          minVal = cb->branches[i].val;
          choice = i;
        }
      }
    //copies the board data from the ComputationBoard to the game board.
    //(I know that a defined copy assignment would be more elegant)
    cb = &(cb->branches[choice]);
    for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
      gb.data[i][j] = cb->data[i][j];
  }
public:
  /**
   * Initializes the AI with given mode.
   */
  Computer (int num, Mode m) : Player(num){
    this->mode = m;
    if(mode == MINMAX){
      std::cout << "Initializing MinMax AI ..." << std::endl;
      cb = new ComputationBoard();
      cb->initTree();
      std::cout << "MinMax AI ready!" << std::endl;
    }
  }

  /**
   * Calculates the AI's move acording to its mode.
   */
  void play(Board& gb) {
    std::cout << "Thinking..." << std::endl;
    if(mode == RANDOM) playRandom(gb);
    else playMinMax(gb);
  }
};
