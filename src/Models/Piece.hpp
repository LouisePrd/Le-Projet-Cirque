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
    
    public:
    Piece();
    Piece(int id, std::string color, int x, int y, bool selected, int idPlayer);

    // Getters
    int getId() const;
    std::string getColor() const;
    int getX() const;
    int getY() const;
    bool isSelected() const;
    int getIdPlayer() const;

    // Setters
    void setId(int id);
    void setX(int x);
    void setY(int y);
    void setSelected(bool selected);
};

#endif