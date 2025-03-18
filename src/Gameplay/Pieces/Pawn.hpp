#ifndef PAWN_HPP
#define PAWN_HPP

#include "../Piece.hpp"
#include <utility>

class Pawn : public Piece {
public:
  Pawn();
  Pawn(int id, std::string color, int x, int y, bool selected, int idPlayer);
  bool isMoveValid(std::pair<int, int> move) override;
  bool firstMove = true;
};

#endif