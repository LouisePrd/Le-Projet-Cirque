#ifndef KING_HPP
#define KING_HPP

#include "../Piece.hpp"
#include "../Board.hpp"

class King : public Piece {
public:
    King(int id, std::string color, int x, int y, bool selected, int idPlayer, Board* board);
    virtual bool isMoveValid(std::pair<int, int> move, Board& board);
};

#endif