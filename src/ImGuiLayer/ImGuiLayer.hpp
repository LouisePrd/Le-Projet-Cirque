#pragma once

#include <GLFW/glfw3.h>

namespace ImGuiLayer {
    void init(GLFWwindow* window);
    void beginFrame();
    void endFrame();
    void shutdown();
}