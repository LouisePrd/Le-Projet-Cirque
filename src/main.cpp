#include "Gameplay/Game.hpp"
#include "UI/MainMenu.hpp"
#include "UI/GameUI.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>

int main() {
  Game game;
  MainMenu mainMenu;
  GameUI gameUI;

  quick_imgui::loop("Le Projet Cirque", [&]() {
    if (mainMenu.running == true)
      game = mainMenu.render();
    else if (gameUI.running == true)
      gameUI.render(game);
  });

  return 0;
}
