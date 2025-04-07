#include "UI/Props/CaseUI.hpp"
#include "Gameplay/Board.hpp"
#include <imgui.h>
#include <iostream>

CaseUI::CaseUI() {}

void CaseUI::renderCase(Case &c, Board &board) {
  int pushCount = 0;

  if (c.piece != nullptr && c.piece->getType() != "") {
    if (c.piece->getColor() == "black") {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    } else {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    }
    pushCount += 2;

    if (board.caseSelected == &c) {
      // Si la case est sélectionnée appartient au joueur actuel
      if (c.piece->getIdPlayer() == board.joueurActuel->getId()) {
      ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
      ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
      } else {
        // Si la case est sélectionnée n'appartient pas au joueur actuel
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
      }
      pushCount++;
    }

    ImGui::Button(c.piece->getType().c_str(), this->buttonSize);

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && board.caseSelected == &c) {
      board.caseSelected = nullptr;
      if (pushCount > 0) {
        ImGui::PopStyleColor(pushCount);
      }
      ImGui::PopStyleVar();
      return;
    }
  

    if (board.caseSelected == &c) {
      ImGui::PopStyleColor(1);
      pushCount--;
      ImGui::PopStyleVar();
    }

  } else { // Si la case est vide
    std::string buttonLabel = "##" + std::to_string(c.id);
    if ((c.x + c.y) % 2 == 0) {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8039f, 0.7059f, 0.8588f, 1.0f)); // Violet clair
    } else {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.7843f, 0.8667f, 1.0f)); // Rose clair
    }

    ImGui::Button(buttonLabel.c_str(), this->buttonSize);

    ImGui::PopStyleColor();
  }

  if (pushCount > 0) {
    ImGui::PopStyleColor(pushCount);
  }

  if (ImGui::IsItemClicked()) {
    selectCase(c, board);
  }
}

void CaseUI::selectCase(Case &c, Board &board) {
  std::cout << "Case selected : " << c.x << " " << c.y << std::endl;

  // Si aucune case n'est sélectionnée
  if (board.caseSelected == nullptr) {
    if (c.piece != nullptr && c.piece->getIdPlayer() == board.joueurActuel->getId()) {
      // Si la case contient une pièce du joueur actuel
      board.caseSelected = &c;
    }
    
  } else { // Si une case est déjà sélectionnée

    if (board.caseSelected == &c) {
      std::cout << "Same case selected" << std::endl;
      board.caseSelected = nullptr;
      return;
    }

    if (c.piece != nullptr && c.piece->getIdPlayer() == board.joueurActuel->getId()) {
      std::cout << "Same player selected" << std::endl;
      return;
    }
    
    if (c.piece == nullptr || c.piece->getIdPlayer() != board.joueurActuel->getId()) {
      std::cout << "Move piece" << std::endl;
      board.movePiece(board.caseSelected, &c);

      board.caseSelected = nullptr;
    } else {
      std::cout << "Invalid move" << std::endl;
    }
  }
}
