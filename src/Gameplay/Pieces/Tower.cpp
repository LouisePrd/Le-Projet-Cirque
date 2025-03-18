#include "Tower.hpp"
#include "Gameplay/Board.hpp"
#include <iostream>
#include <string>

Tower::Tower(int id, std::string color, int x, int y, bool selected,
           int idPlayer) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType("T");
}

bool Tower::isMoveValid(std::pair<int, int> move, Board &board) {
  int currentX = this->getX();
  int currentY = this->getY();
  int targetX = move.first;
  int targetY = move.second;

  std::cout << "Checking Rook move from (" << currentX << "," << currentY 
            << ") to (" << targetX << "," << targetY << ")" << std::endl;

  if (currentX != targetX && currentY != targetY) {
      std::cout << "Invalid move" << std::endl;
      return false;
  }

  std::cout << "Valid move" << std::endl;
  return true;
}