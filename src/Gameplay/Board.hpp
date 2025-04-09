#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <memory>

// Représente une case du plateau
struct Case {
  int id;
  int x;
  int y;
  int color;
  std::unique_ptr<Piece> piece = nullptr;

  void setColor(int color) { this->color = color; }
};

// Plateau de jeu
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

  Board(); // constructeur
  ~Board() = default;

  void createTartan();
  void movePiece(Case *from, Case *to);
  void displayGame();
  void assignPieces();
  bool isCaseEmpty(int x, int y);
  void reset();
  std::vector<Case*> getValidMoves(Piece* piece);
};

int getIndex(int x, int y);

#endif
