#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <tiny_obj_loader.h>

#include "Renderer/Camera.hpp"

class Model {
public:
    Model(const std::string& path);
    ~Model();

    void draw(const Camera& camera);

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    size_t indexCount = 0;

    GLuint shaderProgram = 0;

    bool loadOBJ(const std::string& path);
    void setupBuffers(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices);
    GLuint loadShader(const std::string& vertPath, const std::string& fragPath);
};
