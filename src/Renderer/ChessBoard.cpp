#include "Renderer/ChessBoard.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 ourColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

const char* fragmentSrc = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(ourColor, 1.0);
}
)";

ChessBoard::ChessBoard() {
    init();
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.0f, -0.5f, -4.0f));
    shader = createShader();
}

ChessBoard::~ChessBoard() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader);
}

void ChessBoard::init() {
    std::vector<float> vertices;

    for (int z = 0; z < 8; ++z) {
        for (int x = 0; x < 8; ++x) {
            float xpos = static_cast<float>(x);
            float zpos = static_cast<float>(z);
            bool isWhite = (x + z) % 2 == 0;
            glm::vec3 color = isWhite ? glm::vec3(1.0f) : glm::vec3(0.1f);

            float square[] = {
                xpos,     0.0f, zpos,     color.r, color.g, color.b,
                xpos + 1, 0.0f, zpos,     color.r, color.g, color.b,
                xpos + 1, 0.0f, zpos + 1, color.r, color.g, color.b,

                xpos,     0.0f, zpos,     color.r, color.g, color.b,
                xpos + 1, 0.0f, zpos + 1, color.r, color.g, color.b,
                xpos,     0.0f, zpos + 1, color.r, color.g, color.b,
            };

            vertices.insert(vertices.end(), std::begin(square), std::end(square));
        }
    }

    std::cout << "[ChessBoard] Total vertices: " << vertices.size() / 6 << std::endl;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

GLuint ChessBoard::createShader() {
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSrc, nullptr);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSrc, nullptr);
    glCompileShader(fragment);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vertex);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return prog;
}

void ChessBoard::draw(const Camera& camera) {
    if (shader == 0 || vao == 0) {
        std::cerr << "[ChessBoard] Shader or VAO not initialized." << std::endl;
        return;
    }

    glUseProgram(shader);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    GLint locModel = glGetUniformLocation(shader, "model");
    GLint locView = glGetUniformLocation(shader, "view");
    GLint locProj = glGetUniformLocation(shader, "projection");

    if (locModel == -1 || locView == -1 || locProj == -1) {
        std::cerr << "[ChessBoard] Shader uniform location error." << std::endl;
        return;
    }

    glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 8 * 8 * 6);
    glBindVertexArray(0);
}