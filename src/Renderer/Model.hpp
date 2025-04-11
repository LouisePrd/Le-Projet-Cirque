#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Renderer/Camera.hpp"

class Model {
public:
    Model(const std::string& path);
    ~Model();

    void draw(const Camera& camera);
    void setPosition(const glm::vec3& pos);
    void setScale(float scale);
    void setShader(const std::string& vertexPath, const std::string& fragmentPath);

private:
    GLuint vao = 0, vbo = 0;
    GLuint shader = 0;
    int vertexCount = 0;

    glm::vec3 position = glm::vec3(0.0f);
    float scale = 1.0f;

    bool loadOBJ(const std::string& path);
    void setupBuffers(const std::vector<float>& vertices);
    GLuint loadShader(const std::string& vertexPath, const std::string& fragmentPath);
};
