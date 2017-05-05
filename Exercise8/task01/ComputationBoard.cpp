
/**
 * This class implements a tree of GeneralBoards containing all possible move
 * sequences and their value for the MinMaxAI.
 * The algorithm I tried to implement is discribed here: http://neverstopbuilding.com/minimax
 * I'm not sure if i implemented the value system in the right way.
 */
class ComputationBoard : public GeneralBoard{
public:
  int val;/**< The value of the permutation. Higher number are better for the AI. */
  int layer;/**< The Number of turns since the beginning of the game. */
  std::vector<ComputationBoard> branches; /**<List containing all possible successor boards.*/

  //Constructor for layer 0;
  ComputationBoard() : ComputationBoard(0){  }

  /**
   * Initializes The ComputationBoard with given layer l.
   * @param l the given layer.
   */
  ComputationBoard(int l) : GeneralBoard(){
    val=0;
    layer = l;
    data = new int*[3];
    for (int i = 0; i < 3; i++) {
      data[i] = new int[3];
      for (int j = 0; j < 3; j++)
        data[i][j] = 0;
    }
    branches ={};
  }

  /**
   * Returns the winner of current board and how valuable it is for the AI.
   * @return 10 if the AI won, -10 if the human player won, 0 if nobody won.
   */
  int getWinner() {
    if (playerWins(1)) return -10;
    if (playerWins(2)) return 10;
    // if (isFull()) return 1;
    return 0;
  }

  /**
   * Initializes the the next layer of the tree.
   * @return The value of current board.
   */
  int initTree(){
    int winner = getWinner();
    if(winner == 0){
      //Initializes next layer
      for (int i = 0; i < 9 - layer; i++)
        branches.insert(branches.end(), ComputationBoard(layer + 1));
      //For every free position...
      int currentChoice = -1;
      int lastChoice = -1;
      bool choiceMade = false;
      for (int k = 0; k < branches.size(); k++) {
        for (int i = 0; i < 3; i++)
          for (int j = 0; j < 3; j++)
            if(!choiceMade && data[i][j] == 0){
              currentChoice++;
              //... the data from current board is copied. An one of the free positions is occupied.
              if(currentChoice > lastChoice ) {
                lastChoice = currentChoice;
                branches[k].data[i][j] = (layer % 2) + 1;
                choiceMade = true;
              }
            }else
              branches[k].data[i][j] = data[i][j];
        currentChoice = -1;
        choiceMade = false;
        val += branches[k].initTree();
      }
      return val;
    }
    if(winner > 0) return winner - layer;
    if(winner > 0) return layer - winner;
  }

};
