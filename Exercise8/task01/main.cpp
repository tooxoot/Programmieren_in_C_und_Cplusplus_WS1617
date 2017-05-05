/**
 * I know that all this code is pretty ugly and i should have split the class
 * files into header and source file and should have implemented all the usefull
 * pretty operators... but I'm a sinner and had no time for this.
 */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "GeneralBoard.cpp"
#include "ComputationBoard.cpp"
#include "board.cpp"
#include "player.cpp"
#include "game.cpp"

/**
 * Promts the player for gamemode and starts the game.
 */
int main(int argc, char const *argv[]) {
  while(true){
    std::cout << "Choose your game mode:" << std::endl;
    std::cout << "(1) Human vs. Human" << std::endl;
    std::cout << "(2) Human vs. Computer (Minmax)" << std::endl;
    std::cout << "(3) Human vs. Computer (Random)" << std::endl;
    std::cout << "(4) Exit Program" << std::endl;

    int modechoice = promptFor("", 1, 4);
    GameMode mode;
    switch (modechoice) {
      case 1: mode = HH; break;
      case 2: mode = HM; break;
      case 3: mode = HR; break;
      case 4: return 0;
    }

    Game game(mode);
    int winner = game.start();
    switch (winner) {
      case 1:
      case 2:
        std::cout << "Congratulations Player " << winner << " won!" << std::endl;
        break;
      case -1:
        std::cout << "Nobody won... boring!" << std::endl;
        break;
    }
    std::cout << "" << std::endl;
  }
}
