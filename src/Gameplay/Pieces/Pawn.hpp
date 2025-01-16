#ifndef PAWN_HPP
#define PAWN_HPP

#include "../Piece.hpp"
#include <utility>

class Pawn : public Piece {
public:
  Pawn();
  Pawn(int id, std::string color, int x, int y, bool selected, int idPlayer);

private:
  std::string type;
  int range = 1;
  bool firstMove = true;

  bool isMoveValid(std::pair<int, int> move) override;
};

#endif