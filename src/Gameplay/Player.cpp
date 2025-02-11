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

void Player::play() {
  std::cout << "Player " << this->Pseudo << " is playing" << std::endl;
}
