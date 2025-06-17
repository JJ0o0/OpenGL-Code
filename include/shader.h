#pragma once

#include <glad/glad.h>

#include "glm/ext/vector_float4.hpp"

#include <string>

class Shader {
private:
    unsigned int vertexShader, fragShader;
    unsigned int shaderProgram;

    void CheckShader(GLuint shader, const std::string& type);

    std::string ReadFile(const std::string path);
public:
    Shader(const std::string vertexPath, const std::string fragPath);
    ~Shader();

    void UseProgram();
    void SetVec4Uniform(const char* name, const glm::vec4& value);

    GLuint GetProgram();
};