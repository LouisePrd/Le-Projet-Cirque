#include "UI/Props/CaseUI.hpp"
#include "Gameplay/Game.hpp"
#include "UI/GameUI.hpp"
#include <imgui.h>
#include <iostream>

#include <iostream>

CaseUI::CaseUI() {}

void CaseUI::renderCase(Case &c, Game &game) {
    int pushCount = 0;

    if (c.piece != nullptr && c.piece->getType() != "") {
        std::cout << "Piece : " << c.piece->getType() << std::endl;
        if (c.piece->getColor() == "white") {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        }
        pushCount += 2;

        if (game.caseSelected == &c) {
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
            pushCount++;
        }

        ImGui::Button(c.piece->getType().c_str(), this->buttonSize);

        if (game.caseSelected == &c) {
            ImGui::PopStyleColor(1);
            ImGui::PopStyleVar();
            pushCount--;
        }
    } else { // Si la case est vide
        std::string buttonLabel = "##" + std::to_string(c.id);
        ImGui::Button(buttonLabel.c_str(), this->buttonSize);
    }

    if (pushCount > 0) {
        ImGui::PopStyleColor(pushCount);
    }
}

