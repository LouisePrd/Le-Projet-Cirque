#include "UI/Props/CaseUI.hpp"
#include "Gameplay/Game.hpp"
#include "UI/GameUI.hpp"
#include <imgui.h>

#include <iostream>

CaseUI::CaseUI() {}

void CaseUI::renderCase(Case &c, Game &game) {
  if (c.piece.has_value()) {
    const Piece &p = c.piece.value();

    if (p.getColor() == "white") {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    } else {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    if (game.caseSelected == &c) {
      ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
      ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
    }

    ImGui::Button(p.getType().c_str(), this->buttonSize);

    if (game.caseSelected == &c) {
      ImGui::PopStyleColor(1);
      ImGui::PopStyleVar();
    }
    ImGui::PopStyleColor(2);

    if (ImGui::IsItemClicked() && p.getIdPlayer() == game.joueurActuel->getId())
      game.caseSelected = &c;
  } else {
    std::string buttonLabel = "##" + std::to_string(c.id);
    ImGui::Button(buttonLabel.c_str(), this->buttonSize);
  }
}
