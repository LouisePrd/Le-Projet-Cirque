
#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Player.hpp"

class Game {
public:
  Player player1;
  Player player2;
  Board board;
  Player *joueurActuel;
  Case *caseSelected;

  Game();
  void displayGame();
  void startGame();
};

int getIndex(int x, int y);

#endif
