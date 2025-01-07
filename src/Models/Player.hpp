// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include <string>

class Player {

private:
  int id;
  std::string Pseudo = "";
  std::string Color = "";
  int nbMove;

public:
  Player(int id);
  void setPseudo(std::string pseudo);
  std::string getPseudo();
  void setColor(std::string color);
  std::string getColor();
  void AssignPieces(Board &board);
};

#endif