#include "UI/GameUI.hpp"
#include "Gameplay/Game.hpp"
#include <imgui.h>

#include <iostream>

void GameUI::render(Game &game) {
  ImGui::Begin("Game");
  std::string playerText =
      game.player1.getPseudo() + " VS " + game.player2.getPseudo();
  ImGui::Text("%s", playerText.c_str());
  ImGui::NewLine();

  for (int i = 0; i < game.board.cases.size(); i++) {
    const Case &c = game.board.cases[i];

    if (c.piece.has_value()) {
      const Piece &p = c.piece.value();

      if (p.getColor() == "white") {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
      } else {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
      }

      ImGui::Button(p.getType().c_str(), ImVec2(50, 50));
      ImGui::PopStyleColor(2);
    } else {
      std::string buttonLabel = "##" + std::to_string(c.id);
      ImGui::Button(buttonLabel.c_str(), ImVec2(50, 50));
    }

    if (i % 8 != 7)
      ImGui::SameLine();
  }
  ImGui::End();
}