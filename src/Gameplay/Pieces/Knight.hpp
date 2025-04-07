#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../Board.hpp"
#include "../Piece.hpp"

class Knight : public Piece {
private:
  int range = 2;
  bool firstMove = true;

public:
  Knight(int id, std::string color, int x, int y, bool selected, int idPlayer,
         Board *board);
  virtual bool isMoveValid(std::pair<int, int> move, Board &board);
};

#endif
