#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Piece.hpp"
struct Case {
    int id;
    int x;
    int y;
    int color;
    Piece* piece = nullptr;

    void setColor(int color) {
        this->color = color;
    }
};
class Board {
    public:
        int nbCase;
        int nbPiece;
        std::vector<Case> cases;
        void createTartan();
};
#endif