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
  std::vector<std::vector<Case>> cases;

  Player player1;
  Player player2;
  Player *joueurActuel;
  Case *caseSelected;

  void createTartan();
  void movePiece(Case *from, Case *to);
  void displayGame();
  void startGame();
  void assignPieces();
  Board();
};

int getIndex(int x, int y);

#endif