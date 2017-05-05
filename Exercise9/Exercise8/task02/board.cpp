
class Board : public GeneralBoard {
private:

public:
  Board (){};
  ~Board (){};

  /**
   * Inserts given playernumber into given position if this position is free.
   * @param  playerNumber The inserted number.
   * @param  row          The row in which the number is inserted.
   * @param  col          The column in which the number is inserted.
   * @return              True if the insert wa succsessfull. False if the position
   *                      was already occupied.
   */
  bool insert(int playerNumber, int row, int col) {
    if (!( this->isFree(row, col) )) return false;
    data[row][col] = playerNumber;
    return true;
  }

  /**
   * Returns if the given position is free or not.
   * @param  row The checked row
   * @param  col The checked column
   * @return     True if the position is free.
   */
  bool isFree(int row, int col) { return data[row][col] == 0; }

  /**
   * Returns the current winner.
   * @return 1/2 if Player 1/2 won. -1 If the board is full. 0 else.
   */
  int getWinner() {
    if (playerWins(1)) return 1;
    if (playerWins(2)) return 2;
    if (isFull()) return -1;
    return 0;
  }
};
