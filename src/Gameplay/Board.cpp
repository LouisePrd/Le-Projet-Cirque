#include <iostream>

#include "Board.hpp"
#include "Piece.hpp"
#include "Pieces/Pawn.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <string>
#include <vector>

void Board::createTartan() {
  int id = 0;
  this->cases.clear(); // Réinitialise la grille

  for (int i = 0; i < 8; ++i) {
    std::vector<Case> row;
    for (int j = 0; j < 8; ++j) {
      int color = (i + j) % 2;
      row.push_back({id++, j, i, color});
    }
    this->cases.push_back(std::move(row));
  }
}

void Board::movePiece(Case *from, Case *to) {
  Piece *piece = from->piece;
  if (piece == nullptr) {
    std::cout << "No piece to move" << std::endl;
    return;
  } else if (piece->isMoveValid(std::pair<int, int>(to->x, to->y))) {
    std::cout << "Valid Move" << std::endl;
    to->piece = piece;
    from->piece = nullptr;
  } else {
    std::cout << "Invalid move" << std::endl;
  }
}

void Board::displayGame() {
  this->createTartan();
  std::cout << "Starting with :" << player1.getPseudo() << " and "
            << player2.getPseudo() << std::endl;
  this->assignPieces();
  this->joueurActuel = &player1;
}

void Board::startGame() {


}

Board::Board() : player1(1), player2(2), joueurActuel(&player1), caseSelected(nullptr) {
  this->createTartan();
}

void Board::assignPieces() {
    for (int i = 0; i < 8; i++) {
      this->cases[1][i].piece = new Pawn(1, "black", 1, i, false, 1);
      std::cout << "Piece : " << this->cases[1][i].piece->getType() << " ajoutée en " << this->cases[1][i].x << " " << this->cases[1][i].y << std::endl;
    }
    for (int i = 0; i < 8; i++) {
      this->cases[6][i].piece = new Pawn(1, "white", 6, i, false, 2);
      std::cout << "Piece : " << this->cases[6][i].piece->getType() << " ajoutée en " << this->cases[6][i].x << " " << this->cases[6][i].y << std::endl;
    }
}


