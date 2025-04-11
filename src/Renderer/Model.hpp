#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Renderer/Camera.hpp"

class Model {
public:
    Model(const std::string& path);
    ~Model();

    void draw(const Camera& camera);
    void setPosition(const glm::vec3& pos);
    void setScale(float s);
    void setColor(const glm::vec3& col);

private:
    GLuint vao = 0, vbo = 0;
    GLuint shader = 0;
    int vertexCount = 0;

    glm::vec3 position = glm::vec3(0.0f);
    float scale = 1.0f;
    glm::vec3 color = glm::vec3(0.96f, 0.89f, 0.78f); // Default: beige

    void setupBuffers(const std::vector<float>& vertices);
    bool loadOBJ(const std::string& path);
    GLuint loadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void setShader(const std::string& vertexPath, const std::string& fragmentPath);
};