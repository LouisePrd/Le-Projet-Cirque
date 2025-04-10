#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

#include "Gameplay/Board.hpp"
#include "MainMenu.hpp"
#include "Gameplay/Player.hpp"
#include "Core/GameState.hpp"

extern Board board;

void MainMenu::render(Board &board) {

  ImGui::Begin("Main Menu");
  ImGui::Text("Le Projet Cirque");

  ImGui::Text("Player 1 :");
  ImGui::InputText("##player_one", player_one, 256);
  ImGui::Text("Player 2 :");
  ImGui::InputText("##player_two", player_two, 256);

  if (ImGui::Button("Start game")) {
    if (!checkPseudo(player_one) || !checkPseudo(player_two)) {
      error_message = true;
    } else {
      error_message = false;
      board.player1.setPseudo(std::string(player_one));
      board.player2.setPseudo(std::string(player_two));
      board.displayGame();
      currentGameState = GameState::Playing;
    }
  }


  if (error_message)
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                       "Please enter a pseudo for both players.");

  if (ImGui::Button("Close window"))
    exit(0);

  ImGui::End();
}

bool checkPseudo(char *pseudo) {
  if (strlen(pseudo) == 0)
    return false;
  return true;
}