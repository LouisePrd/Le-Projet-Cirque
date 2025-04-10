#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "UI/MainMenu.hpp"
#include "UI/GameUI.hpp"
#include "Gameplay/Board.hpp"
#include "Core/GameState.hpp"

#include "Renderer/Skybox.hpp"
#include "Renderer/Camera.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "Renderer/Model.hpp"

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

Camera camera;
Board board;
MainMenu mainMenu;
GameUI gameUI;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
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

    Model plateau("Assets/models/plateau.obj"); // ON VA LOAD LE PLATEAU LÀ !!

    // === MAIN LOOP ===
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // === RENDER 3D ===
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();    
        skybox.draw(camera);
        plateau.draw(camera);

        // === RENDER IMGUI ===
        ImGuiLayer::beginFrame();

        if (currentGameState == GameState::Menu)
            mainMenu.render(board);
        else if (currentGameState == GameState::Playing)
            gameUI.render(board);

        ImGuiLayer::endFrame();

        // === EVENTS ===
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGuiLayer::shutdown();
    glfwTerminate();
    return 0;
}
