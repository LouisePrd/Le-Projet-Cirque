#ifndef GAMEUI_HPP
#define GAMEUI_HPP
#pragma once

#include "Gameplay/Board.hpp"

class GameUI {
public:
  bool running = true;
  void render(Board &board);
};

#endif
