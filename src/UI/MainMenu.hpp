#pragma once
#include "Gameplay/Board.hpp"

class MainMenu {
public:
  Board render();
  bool running = true;

private:
  char player_one[128] = {0};
  char player_two[128] = {0};
  bool error_message = false;
};

bool checkPseudo(char *pseudo);
