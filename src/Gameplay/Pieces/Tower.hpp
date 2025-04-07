#pragma once

#include "../Piece.hpp"
#include <utility>
#include "../Board.hpp"

class Tower : public Piece {
public:
Tower();
Tower(int id, std::string color, int x, int y, bool selected, int idPlayer);

private:
  int range = 6;
  bool firstMove = true;
  virtual bool isMoveValid(std::pair<int, int> move, Board &board);
};