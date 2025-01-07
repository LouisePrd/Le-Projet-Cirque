#pragma once

class MainMenu {
public:
  void render();

private:
  bool running = true;
  char player_one[256] = {0};
  char player_two[256] = {0};
};
