#include "MainMenu.hpp"
#include "Models/Player.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

Player player1;
Player player2;

void MainMenu::render() {
  ImGui::Begin("Main Menu");

  ImGui::Text("Le Projet Cirque");

  ImGui::Text("Joueur 1 :");
  ImGui::InputText("##player_one", player_one, 256);
  ImGui::Text("Joueur 2 :");
  ImGui::InputText("##player_two", player_two, 256);

  if (ImGui::Button("Start")) {
    player1.setPseudo(std::string(player_one));
    player2.setPseudo(std::string(player_two));
    std::cout << "Lancement de la partie avec les joueurs "
              << player1.getPseudo() << " et " << player2.getPseudo()
              << std::endl;
    running = false;
  }

  if (ImGui::Button("Leave")) {
    std::cout << "Fermeture de l'application." << std::endl;
    running = false;
  }

  ImGui::End();
}