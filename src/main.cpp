#include "UI/MainMenu.hpp"
#include "Gameplay/Board.hpp"
#include "UI/GameUI.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "Core/GameState.hpp"

int main() {
  Board board;
  MainMenu mainMenu;
  GameUI gameUI;

  quick_imgui::loop("Le Projet Cirque", [&]() {
    if (currentGameState == GameState::Menu)
      mainMenu.render(board);
    else if (currentGameState == GameState::Playing)
      gameUI.render(board);
  });

  return 0;
}
