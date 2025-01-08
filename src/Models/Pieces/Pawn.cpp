#include "Models/Pieces/Pawn.hpp"
#include <iostream>
#include <string>

Pawn::Pawn(int id, std::string color, std::string type, int x, int y, bool selected,
           int idPlayer) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType(type);
}

bool Pawn::isMoveValid(std::pair<int, int> move) {
  int currentX = this->getX();
  int currentY = this->getY();

  int range = this->range;

  if (this->getColor() == "black") {
    if (move.first == currentX && move.second == currentY - range)
      return true;
  } else {
    if (move.first == currentX && move.second == currentY + range)
      return true;
  }

  if (this->firstMove) {
    if (this->getColor() == "black") {
      if (move.first == currentX && move.second == currentY - 2 * range)
        return true;
    } else {
      if (move.first == currentX && move.second == currentY + 2 * range)
        return true;
    }
  }

  return false;
}
