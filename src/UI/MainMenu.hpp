#pragma once
#include "Gameplay/Board.hpp"

class MainMenu {
public:
  void render(Board &board);
  bool running = true;

private:
  char player_one[128] = {0};
  char player_two[128] = {0};
  bool error_message = false;
};

bool checkPseudo(char *pseudo);
