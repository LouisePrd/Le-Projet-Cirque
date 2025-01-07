#include "UI/MainMenu.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

int main() {
  MainMenu menu;

  quick_imgui::loop(
        "Home",
        [&]() {
            menu.render();
        }
  );

  return 0;
}
