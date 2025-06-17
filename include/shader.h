#pragma once

#include <glad/glad.h>

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

    GLuint GetProgram();
};