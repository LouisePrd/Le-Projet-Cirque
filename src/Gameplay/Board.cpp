#include "Board.hpp"
#include "Piece.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Tower.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/CrazyBishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Queen.hpp"
#include <imgui.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

void Board::createTartan() {
  int id = 0;
  this->cases.clear();

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
  if (!from || !to || isGameOver) {
    return;
  }

  Piece *piece = from->piece.get();
  if (!piece) {
    return;
  }

  if (piece->isMoveValid({to->x, to->y}, *this) &&
      piece->getIdPlayer() == this->joueurActuel->getId()) {

    if (to->piece && to->piece->getType() == "K") {
      std::cout << "Victory! Player " << joueurActuel->getId() << " has captured the opponent's King." << std::endl;
      isGameOver = true;
      winnerId = joueurActuel->getId();
    }

    if (to->piece) {
      to->piece.reset();
    }

    to->piece = std::move(from->piece);

    to->piece->setX(to->x);
    to->piece->setY(to->y);

    if (Pawn *p = dynamic_cast<Pawn *>(to->piece.get())) {
      p->firstMove = false;
    }

    if (!isGameOver) {
      this->joueurActuel = (this->joueurActuel == &player1) ? &player2 : &player1;
    }
  }

  this->caseSelected = nullptr;
}

void Board::displayGame() {
  this->createTartan();
  this->assignPieces();
  this->joueurActuel = &player2;
  this->isGameOver = false;
  this->winnerId = 0;
}

Board::Board()
    : player1(1), player2(2), joueurActuel(&player1), caseSelected(nullptr) {
  this->createTartan();
}

void Board::assignPieces() {
  // PIONS
  for (int i = 0; i < 8; i++) {
    this->cases[6][i].piece = std::make_unique<Pawn>(i + 1, "black", i, 6, false, 1, this);
    this->cases[1][i].piece = std::make_unique<Pawn>(i + 1, "white", i, 1, false, 2, this);
  }

  // TOURS
  this->cases[7][0].piece = std::make_unique<Tower>(1, "black", 0, 7, false, 1);
  this->cases[7][7].piece = std::make_unique<Tower>(2, "black", 7, 7, false, 1);
  this->cases[0][0].piece = std::make_unique<Tower>(3, "white", 0, 0, false, 2);
  this->cases[0][7].piece = std::make_unique<Tower>(4, "white", 7, 0, false, 2);

  // CAVALIERS
  this->cases[7][1].piece = std::make_unique<Knight>(1, "black", 1, 7, false, 1, this);
  this->cases[7][6].piece = std::make_unique<Knight>(2, "black", 6, 7, false, 1, this);
  this->cases[0][1].piece = std::make_unique<Knight>(3, "white", 1, 0, false, 2, this);
  this->cases[0][6].piece = std::make_unique<Knight>(4, "white", 6, 0, false, 2, this);

  // FOUS (CrazyBishops)
  this->cases[7][2].piece = std::make_unique<CrazyBishop>(1, "black", 2, 7, false, 1, this);
  this->cases[7][5].piece = std::make_unique<CrazyBishop>(2, "black", 5, 7, false, 1, this);
  this->cases[0][2].piece = std::make_unique<CrazyBishop>(3, "white", 2, 0, false, 2, this);
  this->cases[0][5].piece = std::make_unique<CrazyBishop>(4, "white", 5, 0, false, 2, this);

  // ROIS
  this->cases[7][3].piece = std::make_unique<King>(1, "black", 3, 7, false, 1, this);
  this->cases[0][3].piece = std::make_unique<King>(2, "white", 3, 0, false, 2, this);

  // DAMES
  this->cases[7][4].piece = std::make_unique<Queen>(1, "black", 4, 7, false, 1, this);
  this->cases[0][4].piece = std::make_unique<Queen>(2, "white", 4, 0, false, 2, this);
}

bool Board::isCaseEmpty(int x, int y) {
  return this->cases[y][x].piece == nullptr;
}

std::vector<Case*> Board::getValidMoves(Piece* piece) {
  std::vector<Case*> validMoves;
  if (!piece) return validMoves;

  for (int y = 0; y < 8; ++y) {
    for (int x = 0; x < 8; ++x) {
      if (piece->isMoveValid({x, y}, *this)) {
        validMoves.push_back(&cases[y][x]);
      }
    }
  }

  return validMoves;
}

void Board::reset() {
  this->createTartan();
  this->assignPieces();
  this->joueurActuel = &player1;
  this->isGameOver = false;
  this->winnerId = 0;
  this->caseSelected = nullptr;
  this->highlightedCases.clear();
}