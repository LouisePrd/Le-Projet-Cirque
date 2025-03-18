#include "UI/GameUI.hpp"
#include "Gameplay/Board.hpp"
#include "UI/Props/CaseUI.hpp"
#include <imgui.h>

void GameUI::render(Board &board) {
  ImGui::Begin("Game");
  
  static CaseUI caseUI;

  std::string playerText = board.player1.getPseudo() + " VS " + board.player2.getPseudo();
  ImGui::TextUnformatted(playerText.c_str());
  ImGui::NewLine();

  if (board.joueurActuel) {
    std::string playerTurn = board.joueurActuel->getPseudo() + "'s turn to play";
    ImGui::TextUnformatted(playerTurn.c_str());
    ImGui::NewLine();
  }

  // Affichage du plateau
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      caseUI.renderCase(board.cases[i][j], board);
      if (j < 7)
        ImGui::SameLine();
    }
  }

  ImGui::End();
}
