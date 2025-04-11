#include "Renderer/Model.hpp"
#include <tiny_obj_loader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model(const std::string& path) {
    color = glm::vec3(1.0f); // Couleur par défaut : blanche
    scale = 1.0f;
    loadOBJ(path);
    setShader("Assets/shaders/simple.vert", "Assets/shaders/simple.frag");
}

Model::~Model() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader);
}

void Model::setShader(const std::string& vertexPath, const std::string& fragmentPath) {
    shader = loadShader(vertexPath, fragmentPath);
}

void Model::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Model::setScale(float s) {
    scale = s;
}

void Model::setColor(const glm::vec3& c) {
    color = c;
}

void Model::draw(const Camera& camera) {
    glUseProgram(shader);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = glm::scale(model, glm::vec3(scale));
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    // ENVOI DES MATRICES
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // ENVOI DE LA COULEUR
    glUniform3fv(glGetUniformLocation(shader, "overrideColor"), 1, glm::value_ptr(color));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}


bool Model::loadOBJ(const std::string& path) {
    // std::cout << "[Model] Loading OBJ: " << path << std::endl;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
    if (!warn.empty()) std::cout << "[tinyobj] Warning: " << warn << std::endl;
    if (!err.empty()) std::cerr << "[tinyobj] Error: " << err << std::endl;
    if (!ret) return false;

    std::vector<float> vertices;
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            float vx = attrib.vertices[3 * index.vertex_index + 0];
            float vy = attrib.vertices[3 * index.vertex_index + 1];
            float vz = attrib.vertices[3 * index.vertex_index + 2];
            vertices.push_back(vx);
            vertices.push_back(vy);
            vertices.push_back(vz);
        }
    }

    vertexCount = vertices.size() / 3;
    setupBuffers(vertices);
    return true;
}

void Model::setupBuffers(const std::vector<float>& vertices) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

GLuint Model::loadShader(const std::string& vPath, const std::string& fPath) {
    auto read = [](const std::string& path) -> std::string {
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    };

    std::string vCode = read(vPath);
    std::string fCode = read(fPath);
    const char* vSrc = vCode.c_str();
    const char* fSrc = fCode.c_str();

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vSrc, nullptr);
    glCompileShader(vert);

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fSrc, nullptr);
    glCompileShader(frag);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    glDeleteShader(vert);
    glDeleteShader(frag);

    return prog;
}
