
#include "Camera.hpp"
#include <cmath>

Camera::Camera()
    : currentMode(Mode::ORBITAL), target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), angle(0.0f) {
    position = glm::vec3(5.0f, 6.0f, 5.0f);
}

void Camera::update() {
    if (currentMode == Mode::ORBITAL) {
        angle += 0.01f;
        float radius = 8.0f;
        position.x = sin(angle) * radius;
        position.z = cos(angle) * radius;
        position.y = 5.0f;
    } else {
        position = glm::vec3(6.0f, 12.0f, 6.0f); // vue verticale
    }
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
}

void Camera::switchMode() {
    if (currentMode == Mode::ORBITAL)
        currentMode = Mode::STRATEGIC;
    else
        currentMode = Mode::ORBITAL;
}