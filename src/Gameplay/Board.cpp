#include <iostream>
#include "Board.hpp"
#include "Piece.hpp"
#include "Pieces/Pawn.hpp"
#include "quick_imgui/quick_imgui.hpp"
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

    if (piece->isMoveValid({to->x, to->y})) {
        std::cout << "Valid Move" << std::endl;

        if (to->piece) {
            delete to->piece;
        }
        to->piece = piece;
        from->piece = nullptr;

        if (Pawn *p = dynamic_cast<Pawn *>(piece)) {
            p->firstMove = false;
        }
    } else {
        std::cout << "Invalid move" << std::endl;
    }
}

void Board::displayGame() {
    static bool alreadyStarted = false;
    if (alreadyStarted) return;
    alreadyStarted = true;
    this->createTartan();
    this->assignPieces();
    this->joueurActuel = &player1;
}

Board::Board()
    : player1(1), player2(2), joueurActuel(&player1), caseSelected(nullptr) {
    this->createTartan();
}

void Board::assignPieces() {
    for (int i = 0; i < 8; i++) {
        this->cases[1][i].piece = new Pawn(1, "white", i, 1, false, 1);
        std::cout << "Piece : " << this->cases[1][i].piece->getType()
                  << " ajoutée en " << this->cases[1][i].x << " "
                  << this->cases[1][i].y << std::endl;
    }
    for (int i = 0; i < 8; i++) {
        this->cases[6][i].piece = new Pawn(1, "black", i, 6, false, 2);
        std::cout << "Piece : " << this->cases[6][i].piece->getType()
                  << " ajoutée en " << this->cases[6][i].x << " "
                  << this->cases[6][i].y << std::endl;
    }
}
