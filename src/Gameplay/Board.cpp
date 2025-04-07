#include "Board.hpp"
#include "Piece.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Tower.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/CrazyBishop.hpp"
#include "Pieces/King.hpp"
#include <imgui.h>
#include <iostream>
#include <string>
#include <vector>

void Board::createTartan() {
  int id = 0;
  this->cases.clear(); // Réinitialise la grille

  for (int i = 0; i < 8; ++i) {
    std::vector<Case> row;
    for (int j = 0; j < 8; ++j) {
      int color = (i + j) % 2;
      row.push_back({id++, j, i, color, nullptr});
    }
    this->cases.push_back(std::move(row));
  }
}

void Board::movePiece(Case *from, Case *to) {
  if (!from || !to) {
    return;
  }

  Piece *piece = from->piece;
  if (!piece) {
    return;
  }

  if (piece->isMoveValid({to->x, to->y}, *this) &&
      piece->getIdPlayer() == this->joueurActuel->getId()) {
    if (to->piece) {
      delete to->piece;
    }
    to->piece = piece;
    from->piece = nullptr;

    piece->setX(to->x);
    piece->setY(to->y);

    if (Pawn *p = dynamic_cast<Pawn *>(piece)) {
      p->firstMove = false;
    }
    this->joueurActuel = (this->joueurActuel == &player1) ? &player2 : &player1;
  }
  this->caseSelected = nullptr;
}

void Board::displayGame() {
  static bool alreadyStarted = false;
  if (alreadyStarted)
    return;
  alreadyStarted = true;
  this->createTartan();
  this->assignPieces();
  this->joueurActuel = &player2;
}

Board::Board()
    : player1(1), player2(2), joueurActuel(&player1), caseSelected(nullptr) {
  this->createTartan();
}

void Board::assignPieces() {
  // Assignation des pions aux joueurs
  for (int i = 0; i < 8; i++) {
    this->cases[6][i].piece = new Pawn(1, "black", i, 6, false, 1, this);
  }
  for (int i = 0; i < 8; i++) {
    this->cases[1][i].piece = new Pawn(1, "white", i, 1, false, 2, this);
  }

  // Assignation des tours aux joueurs

  // Joueur 1 (noir)
  this->cases[7][0].piece = new Tower(1, "black", 0, 7, false, 1);
  this->cases[7][7].piece = new Tower(2, "black", 7, 7, false, 1);
  this->cases[7][1].piece = new Knight(1, "black", 1, 7, false, 1, this);
  this->cases[7][6].piece = new Knight(2, "black", 6, 7, false, 1, this);
  this->cases[7][3].piece = new King(1, "black", 2, 7, false, 1, this);
  this->cases[7][2].piece = new CrazyBishop(1, "black", 3, 7, false, 1, this);
  this->cases[7][5].piece = new CrazyBishop(2, "black", 4, 7, false, 1, this);

  // Joueur 2 (blanc)
  this->cases[0][0].piece = new Tower(3, "white", 0, 0, false, 2);
  this->cases[0][7].piece = new Tower(4, "white", 7, 0, false, 2);
  this->cases[0][1].piece = new Knight(3, "white", 1, 0, false, 2, this);
  this->cases[0][6].piece = new Knight(4, "white", 6, 0, false, 2, this);
  this->cases[0][3].piece = new King(2, "white", 2, 0, false, 2, this);
  this->cases[0][2].piece = new CrazyBishop(3, "white", 3, 0, false, 2, this);
  this->cases[0][5].piece = new CrazyBishop(4, "white", 4, 0, false, 2, this);
}

bool Board::isCaseEmpty(int x, int y) {
  return this->cases[y][x].piece == nullptr;
}