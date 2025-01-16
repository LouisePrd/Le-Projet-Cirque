#ifndef CASEUI_HPP
#define CASEUI_HPP
#pragma once

#include "Gameplay/Game.hpp"
#include "Gameplay/Board.hpp"
#include <imgui.h>

class CaseUI {
public:
  ImVec2 buttonSize = ImVec2(50, 50);
  CaseUI();
  void renderCase(Case &c, Game &game);
  void selectCase(Case &c, Game &game);
};

#endif