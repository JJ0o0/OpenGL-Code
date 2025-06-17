#include "window.h"

#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(int width, int height, const char* title) 
    : window_width(width), window_height(height), window_title(title) {}

Window::~Window() {
    if (window) glfwDestroyWindow(window);
    
    glfwTerminate();
}

void Window::Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(
        window_width, window_height, 
        window_title, 
        NULL, NULL
    );

    if (window == NULL) {
        std::cerr << "A criação da janela GLFW falhou!\n";

        window = nullptr;
        glfwTerminate();

        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Não foi possível inicializar o GLAD!\n";
    }
}

void Window::Update() {
    // INPUT
    InputHandling();

    // RENDERIZAR
    glClearColor(.2f, .3f, .3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // EVENTOS E BUFFERS
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::InputHandling() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}