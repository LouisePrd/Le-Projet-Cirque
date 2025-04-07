#include "Pawn.hpp"
#include <iostream>
#include <string>

Pawn::Pawn(int id, std::string color, int x, int y, bool selected, 
           int idPlayer, Board* board) {
  this->setId(id);
  this->setColor(color);
  this->setX(x);
  this->setY(y);
  this->setSelected(selected);
  this->setIdPlayer(idPlayer);
  this->setType("P");
  this->firstMove = true;
}


bool Pawn::isMoveValid(std::pair<int, int> move, Board& board) {
    std::cout << ">> Pawn::isMoveValid called" << std::endl;

    int currentX = this->getX();
    int currentY = this->getY();
    int targetX = move.first;
    int targetY = move.second;
  
    // Direction du mouvement en fonction de la couleur du pion
    int moveDirection = (this->getColor() == "black") ? -1 : 1; // Noirs vont vers le bas (y--), Blancs vers le haut (y++)
  
    // Vérifie si le pion avance d'une case (dans la direction correcte)
    if (targetX == currentX && targetY == currentY + moveDirection) {
        if (board.isCaseEmpty(targetX, targetY)) {
            std::cout << "Valid: moving forward one square" << std::endl;
            return true;
        } else {
            std::cout << "Invalid: square is occupied" << std::endl;
            return false;
        }
    }
  
    // Vérifie si le pion avance de deux cases (premier déplacement uniquement) dans la direction correcte
    if (this->firstMove && targetX == currentX && targetY == currentY + 2 * moveDirection) {
        if (board.isCaseEmpty(targetX, targetY) && board.isCaseEmpty(targetX, currentY + moveDirection)) {
            std::cout << "Valid: first move two squares forward" << std::endl;
            return true;
        } else {
            std::cout << "Invalid: path is blocked" << std::endl;
            return false;
        }
    }
  
    // Vérifie si le pion capture en diagonale
    if (abs(targetX - currentX) == 1 && targetY == currentY + moveDirection) {
        if (!board.isCaseEmpty(targetX, targetY)) {
            std::cout << "Valid: diagonal capture" << std::endl;
            return true;
        } else {
            std::cout << "Invalid: no piece to capture" << std::endl;
            return false;
        }
    }
  
    // Si le mouvement n'est pas valide, on affiche un message
    std::cout << "Invalid move" << std::endl;
    return false;
  }
  