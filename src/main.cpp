#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <vector>

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
            std::cout << "[Init] Changed working directory to: " << root << std::endl;
        } else if (path.find("/build") != std::string::npos) {
            std::string root = path.substr(0, path.find("/build"));
            chdir(root.c_str());
            std::cout << "[Init] Changed working directory to: " << root << std::endl;
        } else {
            std::cout << "[Init] Current working directory: " << path << std::endl;
        }
    } else {
        perror("getcwd() error");
    }
}

// Convertit des coordonnées d’échiquier (0–7, 0–7)
glm::vec3 boardToWorld(float x, float z, float scale = 1.6f) {
    float offset = (scale - 1.0f) * 0.5f;
    float worldX = x - 4.0f - 1.0f - offset;
    float worldZ = z - 4.0f + 0.5f - offset;
    return glm::vec3(worldX, -0.7f, worldZ);
}

int main() {
    setWorkingDirectoryToProjectRoot();

    // === INIT GLFW & OPENGL ===
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Projet Cirque", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // === INIT ImGui ===
    ImGuiLayer::init(window);

    // === INIT 3D SCENE ===
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

    // === Génère 8 pions blancs sur la rangée 2 (z = -1)
    std::vector<std::unique_ptr<Model>> pawns;
    for (int x = 0; x < 8; ++x) {
        auto pawn = std::make_unique<Model>("Assets/models/pawn.obj");
        pawn->setScale(1.6f);
        pawn->setPosition(boardToWorld(x, -1, 1.6f));
        pawns.push_back(std::move(pawn));
    }

    // === WHITE TOWER ===
    // ------- White Tower1
    Model tower1("Assets/models/tower.obj");
    tower1.setScale(1.6f);
    tower1.setPosition(boardToWorld(-0.5f, -0.6f, 1.6f)); 
    tower1.setColor(glm::vec3(1.0f));  
    // ------- White Tower2
    Model tower2("Assets/models/tower.obj");
    tower2.setScale(1.6f);
    tower2.setPosition(boardToWorld(6.5f, -0.6f, 1.6f));
    tower2.setColor(glm::vec3(1.0f));  
    // === BLACK TOWER ===
    // ------- Black Tower1
    Model blackTower1("Assets/models/tower.obj");
    blackTower1.setScale(1.6f);
    blackTower1.setPosition(boardToWorld(-0.5f, 6.4f, 1.6f)); 
    blackTower1.setColor(glm::vec3(0.1f, 0.1f, 0.1f));
    // ------- Black Tower2
    Model blackTower2("Assets/models/tower.obj");
    blackTower2.setScale(1.6f);
    blackTower2.setPosition(boardToWorld(6.5f, 6.4f, 1.6f));
    blackTower2.setColor(glm::vec3(0.1f, 0.1f, 0.1f));
    
    // === WHITE KNIGHT ===
    // ------- White Knight1
    Model knight1("Assets/models/knight.obj");
    knight1.setScale(1.6f);
    knight1.setPosition(boardToWorld(0.5f, -1.3f, 1.6f));
    // ------- White Knight2
    Model knight2("Assets/models/knight.obj");
    knight2.setScale(1.6f);
    knight2.setPosition(boardToWorld(5.5f, -1.3f, 1.6f));
    
    // === BLACK KNIGHT ===
    // ------- Black Knight1
    Model blackKnight1("Assets/models/knight.obj");
    blackKnight1.setScale(1.6f);
    blackKnight1.setPosition(boardToWorld(0.5f, 5.7f, 1.6f));
    blackKnight1.setColor(glm::vec3(0.1f));
    // ------- Black Knight2
    Model blackKnight2("Assets/models/knight.obj");
    blackKnight2.setScale(1.6f);
    blackKnight2.setPosition(boardToWorld(5.5f, 5.7f, 1.6f));
    blackKnight2.setColor(glm::vec3(0.1f));
    // === WHITE CRAZY BISHOP ===
    // ------- White CrazyBishop1
    Model bishop1("Assets/models/bishop.obj");
    bishop1.setScale(1.6f);
    bishop1.setPosition(boardToWorld(1.5f, -2.0f, 1.6f));
    // ------- White CrazyBishop2
    Model bishop2("Assets/models/bishop.obj");
    bishop2.setScale(1.6f);
    bishop2.setPosition(boardToWorld(4.5f, -2.0f, 1.6f));

    // === BLACK CRAZY BISHOP ===
    // ------- Black Bishop1
    Model blackBishop1("Assets/models/bishop.obj");
    blackBishop1.setScale(1.6f);
    blackBishop1.setPosition(boardToWorld(1.5f, 5.0f, 1.6f));
    blackBishop1.setColor(glm::vec3(0.1f));

    // ------- Black Bishop2
    Model blackBishop2("Assets/models/bishop.obj");
    blackBishop2.setScale(1.6f);
    blackBishop2.setPosition(boardToWorld(4.5f, 5.0f, 1.6f));
    blackBishop2.setColor(glm::vec3(0.1f));

    // === WHITE QUEEN ===
    Model queen("Assets/models/queen.obj");
    queen.setScale(1.6f);
    queen.setPosition(boardToWorld(2.5f, 0.0f, 1.6f));
    // === BLACK QUEEN ===
    Model blackQueen("Assets/models/queen.obj");
    blackQueen.setScale(1.6f);
    blackQueen.setPosition(boardToWorld(2.5f, 7.0f, 1.6f));
    blackQueen.setColor(glm::vec3(0.1f));
    
    // === WHITE KING ===
    Model king("Assets/models/king.obj");
    king.setScale(1.6f);
    king.setPosition(boardToWorld(3.5f, 0.5f, 1.6f)); 
    // === BLACK KING ===
    Model blackKing("Assets/models/king.obj");
    blackKing.setScale(1.6f);
    blackKing.setPosition(boardToWorld(3.5f, 7.5f, 1.6f));
    blackKing.setColor(glm::vec3(0.1f));

    // === MAIN LOOP ===
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ===== DRAW =====
        camera.update();
        skybox.draw(camera);
        chessboard.draw(camera);
        // ------ Pieces ------
        // Towers
        tower1.draw(camera);
        tower2.draw(camera);
        blackTower1.draw(camera);
        blackTower2.draw(camera);
        // Knights
        knight1.draw(camera);
        knight2.draw(camera);
        blackKnight1.draw(camera);
        blackKnight2.draw(camera);
        // Bishops
        bishop1.draw(camera);
        bishop2.draw(camera);
        blackBishop1.draw(camera);
        blackBishop2.draw(camera);
        // Queens
        queen.draw(camera);
        blackQueen.draw(camera);
        // Kings
        king.draw(camera);
        blackKing.draw(camera);

        for (auto& pawn : pawns) {
            pawn->draw(camera);
        }

        // === IMGUI ===
        ImGuiLayer::beginFrame();

        if (currentGameState == GameState::Menu)
            mainMenu.render(board);
        else if (currentGameState == GameState::Playing)
            gameUI.render(board);

        ImGuiLayer::endFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGuiLayer::shutdown();
    glfwTerminate();
    return 0;
}
