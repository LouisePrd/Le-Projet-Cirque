#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    enum class Mode { ORBITAL, STRATEGIC };

    Camera();
    void update();
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    void switchMode();

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float angle;
    Mode currentMode;
};
