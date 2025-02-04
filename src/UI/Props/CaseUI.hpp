#ifndef CASEUI_HPP
#define CASEUI_HPP
#pragma once

#include "Gameplay/Board.hpp"
#include <imgui.h>

class CaseUI {
public:
  ImVec2 buttonSize = ImVec2(50, 50);
  CaseUI();
  void renderCase(Case &c, Board &board);
  void selectCase(Case &c, Board &board);
};

#endif