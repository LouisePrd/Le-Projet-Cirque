#ifndef CRAZYBISHOP_HPP
#define CRAZYBISHOP_HPP

#include "../Piece.hpp"
#include "../Board.hpp"

class CrazyBishop : public Piece {
public:
    CrazyBishop(int id, std::string color, int x, int y, bool selected, int idPlayer, Board* board);
    virtual bool isMoveValid(std::pair<int, int> move, Board& board);
};

#endif