#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <vector>
#include <memory>

#include "UI/MainMenu.hpp"
#include "UI/GameUI.hpp"
#include "Gameplay/Board.hpp"
#include "Core/GameState.hpp"

#include "Renderer/Skybox.hpp"
#include "Renderer/Camera.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "Renderer/ChessBoard.hpp"
#include "Renderer/Model.hpp"

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

Camera camera;
Board board;
MainMenu mainMenu;
GameUI gameUI;
bool tabPressedLastFrame = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    bool tabPressedNow = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;
    if (tabPressedNow && !tabPressedLastFrame) {
        camera.switchMode();
    }
    tabPressedLastFrame = tabPressedNow;
}

void setWorkingDirectoryToProjectRoot() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::string path(cwd);
        if (path.find("/bin/Debug") != std::string::npos) {
            std::string root = path.substr(0, path.find("/bin/Debug"));
            chdir(root.c_str());
        } else if (path.find("/build") != std::string::npos) {
            std::string root = path.substr(0, path.find("/build"));
            chdir(root.c_str());
        }
    } else {
        perror("getcwd() error");
    }
}

glm::vec3 boardToWorld(float x, float z, float scale = 1.6f) {
    float offset = (scale - 1.0f) * 0.5f;
    float worldX = x - 4.0f - 1.0f - offset;
    float worldZ = z - 4.0f + 0.5f - offset;
    return glm::vec3(worldX, -0.7f, worldZ);
}

std::unique_ptr<Model> createPiece(const std::string& path, float x, float z, float scale, const glm::vec3& color = glm::vec3(1.0f)) {
    auto model = std::make_unique<Model>(path);
    model->setScale(scale);
    model->setPosition(boardToWorld(x, z, scale));
    model->setColor(color);
    return model;
}

int main() {
    setWorkingDirectoryToProjectRoot();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Projet Cirque", nullptr, nullptr);
    if (!window) return -1;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
    glEnable(GL_DEPTH_TEST);

    ImGuiLayer::init(window);

    Skybox skybox;
    skybox.load({
        "Assets/textures/skybox/right.jpg",
        "Assets/textures/skybox/left.jpg",
        "Assets/textures/skybox/top.jpg",
        "Assets/textures/skybox/bottom.jpg",
        "Assets/textures/skybox/front.jpg",
        "Assets/textures/skybox/back.jpg"
    });

    ChessBoard chessboard;

    std::vector<std::unique_ptr<Model>> whitePieces;
    std::vector<std::unique_ptr<Model>> blackPieces;

    // Pions
    for (int x = 0; x < 8; ++x) {
        whitePieces.push_back(createPiece("Assets/models/pawn.obj", x, -1.0f, 1.6f));
        blackPieces.push_back(createPiece("Assets/models/pawn.obj", x, 4.0f, 1.6f, glm::vec3(0.1f)));
    }

    // Tours
    whitePieces.push_back(createPiece("Assets/models/tower.obj", -0.5f, -0.6f, 1.6f));
    whitePieces.push_back(createPiece("Assets/models/tower.obj", 6.5f, -0.6f, 1.6f));
    blackPieces.push_back(createPiece("Assets/models/tower.obj", -0.5f, 6.4f, 1.6f, glm::vec3(0.1f)));
    blackPieces.push_back(createPiece("Assets/models/tower.obj", 6.5f, 6.4f, 1.6f, glm::vec3(0.1f)));

    // Cavaliers
    whitePieces.push_back(createPiece("Assets/models/knight.obj", 0.5f, -1.3f, 1.6f));
    whitePieces.push_back(createPiece("Assets/models/knight.obj", 5.5f, -1.3f, 1.6f));
    blackPieces.push_back(createPiece("Assets/models/knight.obj", 0.5f, 5.7f, 1.6f, glm::vec3(0.1f)));
    blackPieces.push_back(createPiece("Assets/models/knight.obj", 5.5f, 5.7f, 1.6f, glm::vec3(0.1f)));

    // Fous
    whitePieces.push_back(createPiece("Assets/models/bishop.obj", 1.5f, -2.0f, 1.6f));
    whitePieces.push_back(createPiece("Assets/models/bishop.obj", 4.5f, -2.0f, 1.6f));
    blackPieces.push_back(createPiece("Assets/models/bishop.obj", 1.5f, 5.0f, 1.6f, glm::vec3(0.1f)));
    blackPieces.push_back(createPiece("Assets/models/bishop.obj", 4.5f, 5.0f, 1.6f, glm::vec3(0.1f)));

    // Reine & Roi
    whitePieces.push_back(createPiece("Assets/models/queen.obj", 2.5f, 0.0f, 1.6f));
    whitePieces.push_back(createPiece("Assets/models/king.obj", 3.5f, 0.5f, 1.6f));
    blackPieces.push_back(createPiece("Assets/models/queen.obj", 2.5f, 7.0f, 1.6f, glm::vec3(0.1f)));
    blackPieces.push_back(createPiece("Assets/models/king.obj", 3.5f, 7.5f, 1.6f, glm::vec3(0.1f)));

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();
        skybox.draw(camera);
        chessboard.draw(camera);

        for (auto& p : whitePieces) p->draw(camera);
        for (auto& p : blackPieces) p->draw(camera);

        ImGuiLayer::beginFrame();
        if (currentGameState == GameState::Menu) mainMenu.render(board);
        else if (currentGameState == GameState::Playing) gameUI.render(board);
        ImGuiLayer::endFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGuiLayer::shutdown();
    glfwTerminate();
    return 0;
}
