#include "Models/Piece.hpp"
#include <iostream>
#include <string>

Piece::Piece() {
  id = 0;
  color = "";
  x = 0;
  y = 0;
  selected = false;
  idPlayer = 0;
}

Piece::Piece(int id, std::string color, int x, int y, bool selected, int idPlayer) {
  this->id = id;
  this->color = color;
  this->x = x;
  this->y = y;
  this->selected = selected;
  this->idPlayer = idPlayer;
}

int Piece::getId() const { return id; }
std::string Piece::getColor() const { return color; }
int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
bool Piece::isSelected() const { return selected; }
int Piece::getIdPlayer() const { return idPlayer; }

void Piece::setId(int id) { this->id = id; }
void Piece::setX(int x) { this->x = x; }
void Piece::setY(int y) { this->y = y; }
void Piece::setSelected(bool selected) { this->selected = selected; }
