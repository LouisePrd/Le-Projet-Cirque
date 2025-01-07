#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

class Piece {
    public:
        int id;
        std::string type;
        std::string color;
        int x;
        int y;
        bool selected;
        int idPlayer;

    Piece();
    Piece(int id, std::string type, std::string color, int x, int y, bool selected, int idPlayer);
};

#endif