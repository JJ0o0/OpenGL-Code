#pragma once

#include <glad/glad.h>

#include <stdio.h>

class Mesh {
private:
    GLuint VAO, VBO, EBO;
public:
    Mesh(const float* vertices, size_t verticeSize, const unsigned int* indices, size_t indiceSize);
    ~Mesh();

    void Bind() const;
    void Unbind() const;

    void Draw() const;
};