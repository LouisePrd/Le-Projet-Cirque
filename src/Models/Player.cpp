#include "Player.hpp"
#include "Board.hpp"
#include "Pieces/Pawn.hpp"
#include <iostream>
#include <string>
#include <vector>

Player::Player(int id) {
  this->id = id;
  Pseudo = "";
  Color = "";
  nbMove = 0;
}

int getIndex(int x, int y) { return y * 8 + x; }

void Player::setPseudo(std::string pseudo) { Pseudo = pseudo; }
std::string Player::getPseudo() { return Pseudo; }

void Player::setColor(std::string color) { Color = color; }
std::string Player::getColor() { return Color; }

void Player::AssignPieces(Board &board) {
  if (this->id == 1) {
    for (int i = 0; i < 8; i++) {
      Pawn p = Pawn(i, "white", "P", i, 6, false, 1);
      board.cases[getIndex(i, 6)].piece = p;
    }
  } else {
    for (int i = 0; i < 8; i++) {
      Pawn p = Pawn(i, "black", "P", i, 1, false, 2);
      board.cases[getIndex(i, 1)].piece = p;
    }
  }
}
