
/** Enum containing the different game modes
 *  HH: Human vs Human
 *  HR: Human vs RandomAI
 *  HM: Human vs MinMaxAI
*/
enum GameMode { HH, HR, HM };

/**
 * This class represents the main game. It also contains the Game loop.
 */
class Game {
private:
  Player *player1; /**< Pointer to first Player object */
  Player *player2; /**< Pointer to second Player object */
  Board board = Board();  /**< The main game Board */
public:

  /**
   * Constructor which initializes the main game with given game mode gm.
   */
  Game (GameMode gm){
    srand((unsigned)time(0));
    switch (gm) {
      case HH:
        player1 = new Human(1);
        player2 = new Human(2);
        break;
      case HR:
        player1 = new Human(1);
        player2 = new Computer(2, RANDOM);
        break;
      case HM:
        player1 = new Human(1);
        player2 = new Computer(2, MINMAX);
        break;
    }
  };
  ~Game (){};

  /**
   * Starts the main game loop and returns the winning player number.
   * @return 1 or 2 if player 1 or 2 won and -1 if it was a draw.
   */
  int start(){
    int winner;
    int turn = 0;
    std::cout << board << std::endl;
    std::cout << "Player 1: X" << std::endl;
    std::cout << "Player 2: O" << std::endl;
    //While nobody won
    while ((winner = board.getWinner()) == 0) {
      //Get current players turn
      if(turn % 2 == 0) player1->play(board);
      else player2->play(board);
      std::cout << board << std::endl;
      turn++;
    }
    return winner;
  }

};
