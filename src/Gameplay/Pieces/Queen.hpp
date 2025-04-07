#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "../Piece.hpp"
#include "../Board.hpp"

class Queen : public Piece {
    public:
        Queen(int id, std::string color, int x, int y, bool selected, int idPlayer, Board* board);
        virtual bool isMoveValid(std::pair<int, int> move, Board& board);
        virtual ~Queen() = default;
};


#endif