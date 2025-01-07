#include "Game.hpp"
#include "Models/Board.hpp"
#include "Models/Player.hpp"

#include "quick_imgui/quick_imgui.hpp"

#include <iostream>

Game::Game() : player1(1), player2(2) {}

void Game::StartGame() {
  this->board.createTartan();
  std::cout << "Starting with :" << player1.getPseudo() << " and "
            << player2.getPseudo() << std::endl;
  player1.AssignPieces(this->board);
  player2.AssignPieces(this->board);
}
