#ifndef GAMEUI_HPP
#define GAMEUI_HPP
#pragma once

#include "Gameplay/Game.hpp"

class GameUI {
public:
  bool running = true;
  void render(Game &game);
};

#endif
