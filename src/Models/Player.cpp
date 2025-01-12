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
      board.cases[getIndex(i, 6)].piece = new Pawn(i, "black", i, 6, false, 1);
          
    }
  } else {
    for (int i = 0; i < 8; i++) {
      board.cases[getIndex(i, 1)].piece = new Pawn(i, "white", i, 1, false, 2);
    }
  }
}

void Player::play() {
  std::cout << "Player " << this->Pseudo << " is playing" << std::endl;
}
