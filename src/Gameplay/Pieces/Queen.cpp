#include "Queen.hpp"
#include "Gameplay/Board.hpp"
#include <iostream>
#include <string>

Queen::Queen(int id, std::string color, int x, int y, bool selected,
             int idPlayer, Board *board) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType("Q");
}

bool Queen::isMoveValid(std::pair<int, int> move, Board &board) {
    int currentX = this->getX();
    int currentY = this->getY();
    int targetX = move.first;
    int targetY = move.second;
     
    if (currentX == targetX || currentY == targetY ||
        abs(targetX - currentX) == abs(targetY - currentY)) {
        int dx = (targetX - currentX) > 0 ? 1 : (targetX - currentX) < 0 ? -1 : 0;
        int dy = (targetY - currentY) > 0 ? 1 : (targetY - currentY) < 0 ? -1 : 0;
    
        int x = currentX + dx;
        int y = currentY + dy;
    
        while (x != targetX || y != targetY) {
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
    
    return false;
    }