// Camera.hpp
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();

    void update();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void switchMode();

private:
    enum class Mode { ORBITAL, STRATEGIC };
    Mode currentMode;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float angle; 
};