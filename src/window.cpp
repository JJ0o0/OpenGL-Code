#include "window.h"

#include <cmath>
#include <iostream>

// Array para armazenar os vértices.
float vertices[] = {
    0.5f,  0.5f, 0.0f,      1.0f,  1.0f,
    0.5f, -0.5f, 0.0f,      1.0f,  0.0f,
  -0.5f,-0.5f,0.0f,     0.0f, 0.0f,
  -0.5f, 0.5f,0.0f,     0.0f, 1.0f   
};

// Array para armazenar os indices.
unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

// Define variáveis necessárias para a janela.
Window::Window(int width, int height, const char* title) 
    : window_width(width), window_height(height), window_title(title) {}

// Destroi, se houver, o objeto da janela e desliga o GLFW.
Window::~Window() {
    // Como esses objetos são ponteiros, temos que remover manualmente.
    // O Deconstrutor dos objetos age sozinho.
    delete shader;
    delete texture;
    delete texture2;
    delete mesh;

    if (window) glfwDestroyWindow(window);
    
    glfwTerminate();
}

// Inicializa a janela GLFW e o GLAD.
void Window::Init() {
    // Inicializando GLFW, e definindo hints.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Versão máxima do OpenGL.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // Versão mínima do OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Profile do OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);                     // Janela aumentável.

    // Criando a janela.
    // Aqui passo as variáveis que defini no construtor (window_width, window_height, window_title).
    window = glfwCreateWindow(
        window_width, window_height, 
        window_title, 
        NULL, NULL
    );

    // Caso a janela não conseguir ser criada com sucesso, ele irá dar um erro no terminal e encerrar o programa.
    // Assim, ele vai logo para o deconstrutor.
    if (window == NULL) {
        std::cerr << "A criação da janela GLFW falhou!\n";

        window = nullptr; // Transformando window em null pointer para liberação de memória.
        glfwTerminate();

        return;
    }

    // Faz com que a janela seja o contexto atual.
    glfwMakeContextCurrent(window);

    // Definindo callback de caso a janela for mudada de tamanho (por algum mótivo).
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializando o GLAD. Se não for possível inicializar, acaba retornando um erro no terminal.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Não foi possível inicializar o GLAD!\n";
    }

    // Aqui, criamos as classes.
    mesh = new Mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    texture = new Texture("../assets/images/brick.jpg");
    texture2 = new Texture("../assets/images/wood.jpg");
    shader = new Shader("../assets/shaders/default.vert", "../assets/shaders/default.frag");

    shader->UseProgram();   // Usando o programa do Shader só para setar as texturas no fragment.
    shader->SetIntUniform("texture1", 0); // Falando para o shader usar a textura do slot 0.
    shader->SetIntUniform("texture2", 1); // Mesma coisa do outro, só que usando o slot 1.
}

// Método que roda a cada frame no Game Loop.
void Window::Update() {
    // Input
    InputHandling();

    // Renderização
    glClearColor(.2f, .3f, .3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    texture->Bind(0); // Dando Bind na textura com o index 0.
    texture2->Bind(1); // Dando Bind na segunda textura com o index 1.
    shader->UseProgram();   // Aqui, pedimos para o shader usar o programa gerado para renderizar.
    mesh->Draw();           // E depois, desenhamos o mesh que nós queremos.

    // Eventos e Buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

// Detecção de Input (sem ser via callbacks).
void Window::InputHandling() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// Detecção para caso a janela deve fechar.
bool Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

// Método que define tamanho do viewport para o tamanho da janela.
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}