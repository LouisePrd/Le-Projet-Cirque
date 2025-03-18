#include "Pawn.hpp"
#include "Gameplay/Board.hpp"
#include <iostream>
#include <string>

Pawn::Pawn(int id, std::string color, int x, int y, bool selected,
           int idPlayer) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType("P");
  this->firstMove = true;

}

bool Pawn::isMoveValid(std::pair<int, int> move, Board &board) {
  int currentX = this->getX();
  int currentY = this->getY();
  int targetX = move.first;
  int targetY = move.second;

  int moveDirection = (this->getColor() == "white") ? -1 : 1;

  std::cout << "Checking Pawn move from (" << currentX << "," << currentY 
            << ") to (" << targetX << "," << targetY << ")" << std::endl;

  if (targetX == currentX && targetY == currentY + moveDirection) {
      std::cout << "Valid: moving forward one square" << std::endl;
      return true;
  }

  if (this->firstMove && targetX == currentX && targetY == currentY + 2 * moveDirection) {
      std::cout << "Valid: first move two squares forward" << std::endl;
      return true;
  }

  if (abs(targetX - currentX) == 1 && targetY == currentY + moveDirection) {
      std::cout << "Valid: diagonal capture" << std::endl;
      return true;
  }

  std::cout << "Invalid move" << std::endl;
  return false;
}
