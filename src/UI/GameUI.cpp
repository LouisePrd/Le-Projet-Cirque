#include "UI/GameUI.hpp"
#include "Gameplay/Game.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

void GameUI::render(Game &game) {
  ImGui::Begin("Game");
  for (int i = 0; i < game.board.cases.size(); i++) {
    Case c = game.board.cases[i];

    if (c.piece.has_value()) {
      Piece p = c.piece.value();
      std::string pieceLabel = p.type;
      if (p.color == "black")
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
      else
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
      ImGui::PopStyleColor();

      ImGui::Button(pieceLabel.c_str(), ImVec2(50, 50));
    } else {
      std::string buttonLabel = "##" + std::to_string(c.id);
      ImGui::Button(buttonLabel.c_str(), ImVec2(50, 50));
    }

    if (i % 8 != 7)
      ImGui::SameLine();
  }
  ImGui::End();
}