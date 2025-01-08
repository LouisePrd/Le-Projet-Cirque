#include "Player.hpp"
#include "Board.hpp"
#include "Piece.hpp"
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
      for (int j = 0; j < 2; j++) {
        //Piece p = Piece(i, "P1", "white", i, 6, false, 1);
        //board.cases[getIndex(i, 6+j)].piece = p;
      }
    }
  } else {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 2; j++) {
        //Piece p = Piece(i, "P2", "black", i, 1, false, 2);
        //board.cases[getIndex(i, 1-j)].piece = p;
      }
    }
  }

}
