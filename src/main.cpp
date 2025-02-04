#include "UI/MainMenu.hpp"
#include "Gameplay/Board.hpp"
#include "UI/GameUI.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>

int main() {
  Board board;
  MainMenu mainMenu;
  GameUI gameUI;

  quick_imgui::loop("Le Projet Cirque", [&]() {
    if (mainMenu.running == true)
      board = mainMenu.render();
    else if (gameUI.running == true)
      gameUI.render(board);
  });

  return 0;
}
