#include "Game.hpp"
#include "Models/Board.hpp"
#include "Models/Player.hpp"

#include "quick_imgui/quick_imgui.hpp"

#include <iostream>

Game::Game() {
  player1 = Player();
  player2 = Player();
}

void Game::StartGame(Player &player1, Player &player2) {
  this->board.createTartan();
  this->player1 = player1;
  this->player2 = player2;
  std::cout << "Starting with :" << player1.getPseudo() << " and "
            << player2.getPseudo() << std::endl;
}
