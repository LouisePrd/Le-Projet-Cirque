#include "UI/GameUI.hpp"
#include "Gameplay/Game.hpp"
#include "UI/Props/CaseUI.hpp"
#include <imgui.h>

#include <iostream>

void GameUI::render(Game &game) {
  ImGui::Begin("Game");
  CaseUI caseUI;

  std::string playerText =
      game.player1.getPseudo() + " VS " + game.player2.getPseudo();
  std::string playerTurn = game.joueurActuel->getPseudo() + "'s turn to play";

  ImGui::Text("%s", playerText.c_str());
  ImGui::NewLine();

  ImGui::Text("%s", playerTurn.c_str());
  ImGui::NewLine();

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      caseUI.renderCase(game.board.cases[i][j], game);
      if (j < 7)
        ImGui::SameLine();
    }
  }

  ImGui::End();

  game.startGame();
}
