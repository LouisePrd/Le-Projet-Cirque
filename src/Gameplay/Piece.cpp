#include "Piece.hpp"
#include <iostream>
#include <string>

Piece::Piece() {
  id = 0;
  color = "";
  x = 0;
  y = 0;
  selected = false;
  idPlayer = 0;
  type = "";
}

Piece::Piece(int id, std::string type, std::string color, int x, int y, bool selected, int idPlayer) {
  this->id = id;
  this->color = color;
  this->x = x;
  this->y = y;
  this->selected = selected;
  this->idPlayer = idPlayer;
  this->type = type;
}

bool Piece::isMoveValid(std::pair<int, int> move) {
  return true;
}

int Piece::getId() const { return id; }
std::string Piece::getColor() const { return color; }
int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
bool Piece::isSelected() const { return selected; }
int Piece::getIdPlayer() const { return idPlayer; }
std::string Piece::getType() const { return type; }


void Piece::setId(int id) { this->id = id; }
void Piece::setX(int x) { this->x = x; }
void Piece::setY(int y) { this->y = y; }
void Piece::setSelected(bool selected) { this->selected = selected; }
void Piece::setIdPlayer(int idPlayer) { this->idPlayer = idPlayer; }
void Piece::setColor(std::string color) { this->color = color; }
void Piece::setType(std::string type) { this->type = type; }
