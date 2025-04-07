#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

class Piece {
protected:
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
  virtual bool isMoveValid(std::pair<int, int> move, class Board& board) = 0;

  virtual ~Piece() = default;

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