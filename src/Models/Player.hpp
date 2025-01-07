// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {

private:
  int id;
  std::string Pseudo = "";
  std::string Color = "";
  int nbMove;

public:
  Player();
  void setPseudo(std::string pseudo);
  std::string getPseudo();
  void setColor(std::string color);
  std::string getColor();
};

#endif