#pragma once

#include "shader.h"
#include "mesh.h"
#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* window = nullptr;
    int window_width, window_height;
    const char* window_title;

    Mesh* mesh;
    Texture* texture;
    Texture* texture2;
    Shader* shader;

    unsigned int VBO, VAO;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    Window(int width, int height, const char* title);
    ~Window();

    void Init();
    void Update();
    void InputHandling();

    bool ShouldClose();
};