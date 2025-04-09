#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
struct Case {
  int id;
  int x;
  int y;
  int color;
  Piece *piece = nullptr;

  void setColor(int color) { this->color = color; }
};
class Board {
public:
  int nbCase;
  int nbPiece;
  int winnerId = 0;
  bool isGameOver = false;
  std::vector<std::vector<Case>> cases;
  std::vector<Case*> highlightedCases;

  Player player1;
  Player player2;
  Player *joueurActuel;
  Case *caseSelected;

  void createTartan();
  void movePiece(Case *from, Case *to);
  void displayGame();
  void assignPieces();
  bool isCaseEmpty(int x, int y);
  std::vector<Case*> getValidMoves(Piece* piece);
  Board();
};

int getIndex(int x, int y);

#endif