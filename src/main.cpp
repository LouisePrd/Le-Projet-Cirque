#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>
#include <filesystem>

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

glm::vec3 boardToWorld(int x, int z) {
    float worldX = x - 1.0f - 4.0f;
    float worldZ = z + 0.5f - 4.0f;
    return glm::vec3(worldX, 0.0f, worldZ);
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

    // === Charge et positionne un pion OBJ à la case e2 ===
    Model pawn("Assets/models/pawn.obj");
    pawn.setScale(1.4f);                          // Ajuste si nécessaire
    pawn.setPosition(boardToWorld(4, -1));         // e2 → (4,-1)

    // === MAIN LOOP ===
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();
        skybox.draw(camera);
        chessboard.draw(camera);
        pawn.draw(camera);

        // === RENDER IMGUI ===
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
