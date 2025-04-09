#include "UI/GameUI.hpp"
#include "Gameplay/Board.hpp"
#include "UI/Props/CaseUI.hpp"
#include "Core/GameState.hpp"
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

  if (board.isGameOver) {
    ImGui::OpenPopup("Game Over");
  }
  
  if (ImGui::BeginPopupModal("Game Over", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
      "Player %d has won the game by capturing the King!", board.winnerId);
  
    if (ImGui::Button("Rejouer")) {
      board.displayGame(); // relance la partie
      ImGui::CloseCurrentPopup();
    }
  
    ImGui::SameLine();
  
    if (ImGui::Button("Menu principal")) {
      currentGameState = GameState::Menu;
      board.isGameOver = false;
      board.reset();
      ImGui::CloseCurrentPopup();
    }
  
    ImGui::EndPopup();
  }  

  // Separation Texte-Plateau
  ImGui::Separator();

  // Affichage du plateau
  for (int i = 7; i >= 0; i--) {  // Inverser la boucle pour afficher de bas en haut
    for (int j = 0; j < 8; j++) {
        caseUI.renderCase(board.cases[i][j], board);  // Afficher les cases de bas en haut
        if (j < 7)
            ImGui::SameLine();
    }
}


  ImGui::End();
}
