#ifndef PAWN_HPP
#define PAWN_HPP

#include "../Piece.hpp"
#include "../Board.hpp"

class Pawn : public Piece {
public:
    bool firstMove;

public:
    Pawn(int id, std::string color, int x, int y, bool selected, int idPlayer, Board* board);
    virtual bool isMoveValid(std::pair<int, int> move, Board& board);
    void eat(std::pair<int, int> move);
};

#endif
