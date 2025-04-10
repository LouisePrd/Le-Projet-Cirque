#pragma once

#include <vector>
#include <string>
#include "Renderer/Camera.hpp"

class Skybox {
public:
    void load(const std::vector<std::string>& faces);
    void draw(const Camera& camera);

private:
    unsigned int cubemapTexture;
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int shaderProgram;

    void setupMesh();
    unsigned int loadCubemap(const std::vector<std::string>& faces);
    unsigned int loadShader(const char* vertexPath, const char* fragmentPath);
};