#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

#include "Gameplay/Game.hpp"
#include "MainMenu.hpp"
#include "Models/Player.hpp"

Player player1;
Player player2;
Game game;

Game MainMenu::render() {
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
      std::cout << "Lancement de la partie." << std::endl;
      player1.setPseudo(std::string(player_one));
      player2.setPseudo(std::string(player_two));
      game.StartGame(player1, player2);
      running = false;
    }
  }

  if (error_message)
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                       "Please enter a pseudo for both players.");

  if (ImGui::Button("Close window"))
    exit(0);

  ImGui::End();
  return game;
}

bool checkPseudo(char *pseudo) {
  if (strlen(pseudo) == 0)
    return false;
  return true;
}