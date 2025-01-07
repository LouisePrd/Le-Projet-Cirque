#include "UI/GameUI.hpp"
#include "Gameplay/Game.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

void GameUI::render(Game &game) {
  ImGui::Begin("Game");
  ImGui::Text("Game is running");
  ImGui::End();
}