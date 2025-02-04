#include "UI/Props/CaseUI.hpp"
#include "Gameplay/Board.hpp"
#include "UI/GameUI.hpp"
#include <imgui.h>
#include <iostream>

#include <iostream>

CaseUI::CaseUI() {}

void CaseUI::renderCase(Case &c, Board &board) {
    int pushCount = 0;

    if (c.piece != nullptr && c.piece->getType() != "") {
        if (c.piece->getColor() == "white") {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        }
        pushCount += 2;

        if (board.caseSelected == &c) {
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
            pushCount++;
        }

        ImGui::Button(c.piece->getType().c_str(), this->buttonSize);

        if (board.caseSelected == &c) {
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

    if(ImGui::IsItemClicked()) {
        selectCase(c, board);
    }
}

void CaseUI::selectCase(Case &c, Board &board) {
    std::cout << "Case selected : " << c.x << " " << c.y << std::endl;
    if (board.caseSelected == nullptr) {
        board.caseSelected = &c;
    } else {
        board.movePiece(board.caseSelected, &c);
        board.caseSelected = nullptr;
    }
}