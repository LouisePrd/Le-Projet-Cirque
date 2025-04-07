#include <iostream>
#include "Board.hpp"
#include "Piece.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Tower.hpp"
#include <imgui.h>
#include <string>
#include <vector>

void Board::createTartan() {
    int id = 0;
    this->cases.clear(); // Réinitialise la grille

    for (int i = 0; i < 8; ++i) {
        std::vector<Case> row;
        for (int j = 0; j < 8; ++j) {
            int color = (i + j) % 2;
            row.push_back({id++, j, i, color, nullptr}); // Ajout d'un pointeur pièce initialisé à nullptr
        }
        this->cases.push_back(std::move(row));
    }
}

void Board::movePiece(Case *from, Case *to) {
    if (!from || !to) {
        return;
    }
    
    Piece *piece = from->piece;
    if (!piece) {
        return;
    }

    std::cout << "Trying to move " << piece->getType() << " from (" 
              << from->x << "," << from->y << ") to (" 
              << to->x << "," << to->y << ")" << std::endl;

    std::cout << "Piece color: " << piece->getColor() << std::endl;
    std::cout << "Piece player ID: " << piece->getIdPlayer() << std::endl;
    std::cout << "Current player ID: " << this->joueurActuel->getId() << std::endl;
    std::cout << "Is case empty: " << (this->isCaseEmpty(to->x, to->y) ? "Yes" : "No") << std::endl;

    if (piece->isMoveValid({to->x, to->y}, *this ) && piece->getIdPlayer() == this->joueurActuel->getId()) {
        if (to->piece) {
            delete to->piece;
        }
        to->piece = piece;
        from->piece = nullptr;

        piece->setX(to->x);
        piece->setY(to->y);

        if (Pawn *p = dynamic_cast<Pawn *>(piece)) {
            p->firstMove = false;
        }
        this->joueurActuel = (this->joueurActuel == &player1) ? &player2 : &player1;
    }
    this->caseSelected = nullptr;
}

void Board::displayGame() {
    static bool alreadyStarted = false;
    if (alreadyStarted) return;
    alreadyStarted = true;
    this->createTartan();
    this->assignPieces();
    this->joueurActuel = &player2;
}

Board::Board()
    : player1(1), player2(2), joueurActuel(&player1), caseSelected(nullptr) {
    this->createTartan();
}

void Board::assignPieces() {
for (int i = 0; i < 8; i++) {
    this->cases[6][i].piece = new Pawn(1, "black", i, 6, false, 1, this);
}
for (int i = 0; i < 8; i++) {
    this->cases[1][i].piece = new Pawn(1, "white", i, 1, false, 2, this);
}
}

bool Board::isCaseEmpty(int x, int y) {
    return this->cases[y][x].piece == nullptr;
}