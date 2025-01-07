#include "Models/Piece.hpp"
#include <iostream>
#include <string>

Piece::Piece() {
  id = 0;
  type = "";
  color = "";
  x = 0;
  y = 0;
  selected = false;
  idPlayer = 0;
}

Piece::Piece(int id, std::string type, std::string color, int x, int y, bool selected, int idPlayer) {
  this->id = id;
  this->type = type;
  this->color = color;
  this->x = x;
  this->y = y;
  this->selected = selected;
  this->idPlayer = idPlayer;
}