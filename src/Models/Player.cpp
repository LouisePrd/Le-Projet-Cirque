#include "Player.hpp"
#include <iostream>
#include <string>

Player::Player() {
  Pseudo = "";
  Color = "";
  nbMove = 0;
}

void Player::setPseudo(std::string pseudo) { Pseudo = pseudo; }
std::string Player::getPseudo() { return Pseudo; }

void Player::setColor(std::string color) { Color = color; }
std::string Player::getColor() { return Color; }