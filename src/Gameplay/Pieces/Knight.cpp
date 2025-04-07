#include "Knight.hpp"
#include "Gameplay/Board.hpp"
#include <iostream>
#include <string>

Knight::Knight(int id, std::string color, int x, int y, bool selected,
               int idPlayer, Board *board) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType("K");
}

bool Knight::isMoveValid(std::pair<int, int> move, Board &board) {
  int currentX = this->getX();
  int currentY = this->getY();
  int targetX = move.first;
  int targetY = move.second;

  std::cout << "Checking Knight move from (" << currentX << "," << currentY
            << ") to (" << targetX << "," << targetY << ")" << std::endl;

  // Vérifie si le mouvement est en forme de L
  if ((abs(targetX - currentX) == 2 && abs(targetY - currentY) == 1) ||
      (abs(targetX - currentX) == 1 && abs(targetY - currentY) == 2)) {
    // Vérifie si la case cible est occupée par une pièce de la même couleur
    Piece *targetPiece = board.cases[targetY][targetX].piece;
    if (targetPiece && targetPiece->getColor() == this->getColor()) {
      std::cout << "Invalid move: cannot capture ally at (" << targetX << ","
                << targetY << ")" << std::endl;
      return false;
    }
    return true;
  }

  std::cout << "Invalid move: not a valid knight move" << std::endl;
  return false;
}

