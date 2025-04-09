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

  std::cout << "Checking Tower move from (" << currentX << "," << currentY 
            << ") to (" << targetX << "," << targetY << ")" << std::endl;

  // Mouvement en ligne droite seulement
  if (currentX != targetX && currentY != targetY) {
    std::cout << "Invalid move: not a straight line" << std::endl;
    return false;
  }

  // Déplacement horizontal
  if (currentY == targetY) {
    int direction = (targetX > currentX) ? 1 : -1;
    for (int x = currentX + direction; x != targetX; x += direction) {
      if (board.cases[currentY][x].piece) {
        std::cout << "Invalid move: path blocked at (" << x << "," << currentY << ")" << std::endl;
        return false;
      }
    }
  }

  // Déplacement vertical
  if (currentX == targetX) {
    int direction = (targetY > currentY) ? 1 : -1;
    for (int y = currentY + direction; y != targetY; y += direction) {
      if (board.cases[y][currentX].piece) {
        std::cout << "Invalid move: path blocked at (" << currentX << "," << y << ")" << std::endl;
        return false;
      }
    }
  }

  // Vérifie si la case cible est occupée par une pièce de la même couleur
  const auto& targetPiece = board.cases[targetY][targetX].piece;
  if (targetPiece && targetPiece->getColor() == this->getColor()) {
    std::cout << "Invalid move: cannot capture ally at (" << targetX << "," << targetY << ")" << std::endl;
    return false;
  }

  std::cout << "Valid move" << std::endl;
  return true;
}
