#pragma once
#include "Gameplay/Game.hpp"

class MainMenu {
public:
  Game render();
  bool running = true;

private:
  char player_one[128] = {0};
  char player_two[128] = {0};
  bool error_message = false;
};

bool checkPseudo(char *pseudo);
