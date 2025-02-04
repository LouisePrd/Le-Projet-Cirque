#include <iostream>

#include "Board.hpp"
#include "Piece.hpp"
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
  //player1.AssignPieces(this);
  //player2.AssignPieces(this);
  this->joueurActuel = &player1;
}

void Board::startGame() {
  //std::cout << "Game started" << std::endl;
  //player1.play();

}

Board::Board() : player1(1), player2(2), joueurActuel(&player1), caseSelected(nullptr) {
  this->createTartan();
}

