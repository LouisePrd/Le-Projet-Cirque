#include "UI/GameUI.hpp"
#include "Gameplay/Board.hpp"
#include "UI/Props/CaseUI.hpp"
#include <imgui.h>

#include <iostream>

void GameUI::render(Board &board) {
  ImGui::Begin("Game");
  CaseUI caseUI;

  std::string playerText =
      board.player1.getPseudo() + " VS " + board.player2.getPseudo();
  std::string playerTurn = board.joueurActuel->getPseudo() + "'s turn to play";

  ImGui::Text("%s", playerText.c_str());
  ImGui::NewLine();

  ImGui::Text("%s", playerTurn.c_str());
  ImGui::NewLine();

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      caseUI.renderCase(board.cases[i][j], board);
      if (j < 7)
        ImGui::SameLine();
    }
  }

  ImGui::End();

  board.startGame();
}
