#include <iostream>

#include "Board.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <string>
#include <vector>

void Board::createTartan() {
  int id = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Case c;

      if ((i + j) % 2 == 0)
        c = {id, i, i, 0};
      else
        c = {id, i, i, 1};

      id++;
      this->cases.push_back(c);
    }
  }
}
