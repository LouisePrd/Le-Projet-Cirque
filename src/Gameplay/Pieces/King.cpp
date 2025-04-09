#include "King.hpp"
#include <iostream>
#include <string>
#include <cmath>

King::King(int id, std::string color, int x, int y, bool selected,
           int idPlayer, Board* board) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType("K");
}

bool King::isMoveValid(std::pair<int, int> move, Board& board) {
  int currentX = this->getX();
  int currentY = this->getY();
  int targetX = move.first;
  int targetY = move.second;

  if (std::abs(targetX - currentX) <= 1 && std::abs(targetY - currentY) <= 1) {
    const auto& targetPiece = board.cases[targetY][targetX].piece;
    if (targetPiece && targetPiece->getColor() == this->getColor()) {
      return false;
    }
    return true;
  }

  std::cout << "Invalid move: not a valid king move" << std::endl;
  return false;
}
