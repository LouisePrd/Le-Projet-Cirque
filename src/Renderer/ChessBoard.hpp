#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Camera.hpp"

class ChessBoard {
public:
    ChessBoard();
    ~ChessBoard();
    float currentAngle = 0.0f;
    float lastTime = 0.0f;

    void draw(const Camera& camera);

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint shader = 0;

    glm::mat4 modelMatrix;

    void init();
    GLuint createShader();
};
