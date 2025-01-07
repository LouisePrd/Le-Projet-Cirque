
#ifndef GAME_HPP
#define GAME_HPP

#include "Models/Board.hpp"
#include "Models/Player.hpp"

class Game {
public:
  Player player1;
  Player player2;
  Board board;

  Game();
  void StartGame(Player &player1, Player &player2);
  void createBoard();
};

#endif
