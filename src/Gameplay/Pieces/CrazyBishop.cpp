#include "CrazyBishop.hpp"
#include <iostream>
#include <string>
#include <cmath>

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
  int startX = this->getX();
  int startY = this->getY();
  int targetX = move.first;
  int targetY = move.second;

  std::cout << "CrazyBishop from (" << startX << "," << startY
            << ") to (" << targetX << "," << targetY << ")" << std::endl;

  // Mouvement strictement diagonal
  int dx = targetX - startX;
  int dy = targetY - startY;

  if (std::abs(dx) != std::abs(dy)) {
    std::cout << "Pas une diagonale valide." << std::endl;
    return false;
  }

  int stepX = (dx > 0) ? 1 : -1;
  int stepY = (dy > 0) ? 1 : -1;

  int x = startX + stepX;
  int y = startY + stepY;

  while (x != targetX && y != targetY) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
      std::cerr << "Débordement hors du plateau (" << x << "," << y << ")" << std::endl;
      return false;
    }

    if (board.cases[y][x].piece) {
      std::cout << "Obstacle sur le chemin en (" << x << "," << y << ")" << std::endl;
      return false;
    }

    x += stepX;
    y += stepY;
  }

  const auto& targetPiece = board.cases[targetY][targetX].piece;
  if (targetPiece && targetPiece->getColor() == this->getColor()) {
    std::cout << "Case finale occupée par une pièce alliée." << std::endl;
    return false;
  }

  return true;
}