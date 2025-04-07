#include "CrazyBishop.hpp"
#include <iostream>
#include <string>

CrazyBishop::CrazyBishop(int id, std::string color, int x, int y, bool selected,
                         int idPlayer, Board *board) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType("B");
}

bool CrazyBishop::isMoveValid(std::pair<int, int> move, Board &board) {
  // Valide = diagonale
  std::cout << "Checking CrazyBishop move from (" << this->getX() << ","
            << this->getY() << ") to (" << move.first << "," << move.second
            << ")" << std::endl;
  int currentX = this->getX();
  int currentY = this->getY();
  int targetX = move.first;
  int targetY = move.second;

  if (abs(targetX - currentX) == abs(targetY - currentY)) {
    int dx = (targetX - currentX) > 0 ? 1 : -1;
    int dy = (targetY - currentY) > 0 ? 1 : -1;

    int x = currentX + dx;
    int y = currentY + dy;

    while (x != targetX && y != targetY) {
      if (board.cases[y][x].piece != nullptr) {
        return false; // Obstacle
      }
      x += dx;
      y += dy;
    }

    Piece *targetPiece = board.cases[targetY][targetX].piece;
    if (targetPiece && targetPiece->getColor() == this->getColor()) {
      return false;
    }

    return true;
  }

  std::cout << "Move too crazy for this crazy bishop" << std::endl;
  return false;
}
