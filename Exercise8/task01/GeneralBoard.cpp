/**
 * Represents the base gameboard used for the main game and to compute the MINMAX AI.
 */
class GeneralBoard{
public:
  int** data;/**< Array storing the Board values */

  /**
   * Initializes the board array
   */
  GeneralBoard(){
    data = new int*[3];
    for (int i = 0; i < 3; i++) {
      data[i] = new int[3];
      for (int j = 0; j < 3; j++)
        data[i][j] = 0;
    }
  };

  /** Friendfunction to print the Board in a pretty manner. */
  friend std::ostream& operator<<(std::ostream& os, const GeneralBoard& GeneralBoard);

  /**
   * Operator to compare if the actual Board and any ComputationBoard contain the
   * same values.
   */
  bool operator==(const GeneralBoard& lGB){
   for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if(data[i][j] != lGB.data[i][j]) return false;
    return true;
 }

 /**
  * Clears the board to zeros.
  */
 void clearBoard(){
   for(int i = 0; i < 3; i++)
     for(int j = 0; j < 3; j++) data[i][j] = 0;
 }

 /**
 * Checks if all position of the board are occupied.
 * @return True if all positions contain either 1(X) or 2(O).
 */
 bool isFull(){
   bool full = true;
   for(int i = 0; i < 3; i++)
     for(int j = 0; j < 3; j++) full = full && (data[i][j] != 0);
   return full;
 }

  /**
  * Counts all the free positions on the Board.
  * @return The Number of free positions.
  */
 int countFree(){
   int free = 0;
   for(int i = 0; i < 3; i++)
     for(int j = 0; j < 3; j++)
       if (data[i][j] != 0) free++;
   return free;
 }

 /**
 * Calculates the winner of current board. Is implemented in Board and ComputationBoard.
 */
 virtual int getWinner(){};

 /**
  * Calculates if given player is winning.
  * @param  playerNumber The of number of the ckecked Player
  * @return              True if given player has three in a row.
  */
 bool playerWins(int playerNumber){
   //checks all rows
   bool isWinning = true;
   for(int i = 0; i < 3; i++){
     for(int j = 0; j < 3; j++) isWinning = isWinning && (data[i][j] == playerNumber);
     if (isWinning) return true;
     isWinning = true;
   }
   //checks all columns
   for(int i = 0; i < 3; i++){
     for(int j = 0; j < 3; j++) isWinning = isWinning && (data[j][i] == playerNumber);
     if (isWinning) return true;
     isWinning = true;
   }
   //checks all diagonales
   for (int i = 0; i < 3; i++) isWinning = isWinning && (data[i][i] == playerNumber);
   if (isWinning) return true;
   isWinning = true;

   for (int i = 0; i < 3; i++) isWinning = isWinning && (data[2-i][i] == playerNumber);
   return isWinning;
 }

 /**
  * Returns the boardvalue on given position.
  * (Kind of obsolete because out of convinience data is now public)
  */
 int get(int row, int col) const { return this->data[row][col]; }

 /**
  * Returns the symbol to be placed on given position.
  * @param  row The row to get
  * @param  col The column to get
  * @return     Returns the Players Symbol (X/O) or ' '.
  */
 char getXO(int row, int col) const {
   switch (this->data[row][col]) {
     case 0: return ' ';
     case 1: return 'X';
     case 2: return 'O';
   }
   return 'E';
 }

};

//Friend operator discribed above.
std::ostream& operator<<(std::ostream& os, const GeneralBoard& board){
  std::cout << "    1   2   3 " << std::endl;
  std::cout << "  -------------" << std::endl;
  std::cout << "1 | " << board.getXO(0, 0) << " | " << board.getXO(0, 1) << " | " << board.getXO(0, 2) << " |" << std::endl;
  std::cout << "  -------------" << std::endl;
  std::cout << "2 | " << board.getXO(1, 0) << " | " << board.getXO(1, 1) << " | " << board.getXO(1, 2) << " |" << std::endl;
  std::cout << "  -------------" << std::endl;
  std::cout << "3 | " << board.getXO(2, 0) << " | " << board.getXO(2, 1) << " | " << board.getXO(2, 2) << " |" << std::endl;
  std::cout << "  -------------" << std::endl;
  return os;
}
