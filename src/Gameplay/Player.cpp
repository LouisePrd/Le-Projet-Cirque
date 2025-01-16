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
int Player::getId() { return id; }

void Player::setPseudo(std::string pseudo) { Pseudo = pseudo; }
std::string Player::getPseudo() { return Pseudo; }

void Player::setColor(std::string color) { Color = color; }
std::string Player::getColor() { return Color; }

void Player::AssignPieces(Board &board) {
  if (this->id == 1) {
    for (int i = 0; i < 8; i++) {
      board.cases[1][i].piece = new Pawn(1, "black", 1, i, false, 1);
      std::cout << "Piece : " << board.cases[1][i].piece->getType() << " ajoutée en " << board.cases[1][i].x << " " << board.cases[1][i].y << std::endl;
    }
  } else {
    for (int i = 0; i < 8; i++) {
      board.cases[6][i].piece = new Pawn(1, "white", 6, i, false, 2);
      std::cout << "Piece : " << board.cases[6][i].piece->getType() << " ajoutée en " << board.cases[6][i].x << " " << board.cases[6][i].y << std::endl;
    }
  }
}

void Player::play() {
  std::cout << "Player " << this->Pseudo << " is playing" << std::endl;
}
