#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
struct Case {
    int id;
    int x;
    int y;
    int color;
    std::string piece;
};
class Board {
    public:
        int nbCase;
        int nbPiece;
        std::vector<Case> cases;
        void createTartan();
};

#endif