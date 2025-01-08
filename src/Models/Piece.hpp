#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

class Piece {
private:
  int id;
  std::string color;
  int x;
  int y;
  bool selected;
  int idPlayer;
  std::string type;

public:
  Piece();
  Piece(int id, std::string type, std::string color, int x, int y, bool selected, int idPlayer);
  bool move(int x, int y);

  // Getters
  int getId() const;
  std::string getColor() const;
  int getX() const;
  int getY() const;
  bool isSelected() const;
  int getIdPlayer() const;
  std::string getType() const;

  // Setters
  void setId(int id);
  void setX(int x);
  void setY(int y);
  void setSelected(bool selected);
  void setIdPlayer(int idPlayer);
  void setColor(std::string color);
  void setType(std::string type);
};

#endif