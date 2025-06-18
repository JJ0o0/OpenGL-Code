#include "shader.h"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

// Aqui onde criaremos os shaders de acordo com o diretório.
Shader::Shader(const std::string vertexPath, const std::string fragPath) {
    // Primeiro lemos os arquivos dos diretórios.
    std::string vertexSource = ReadFile(vertexPath);
    std::string fragmentSource = ReadFile(fragPath);

    // Transformamos em uma array de caracteres.
    const char* vertexCode = vertexSource.c_str();
    const char* fragCode = fragmentSource.c_str();

    // Criamos o shader e verificamos por erros.
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);
    CheckShader(vertexShader, "Vertex");

    // Mesma coisa para o Fragment Shader.
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragCode, NULL);
    glCompileShader(fragShader);
    CheckShader(fragShader, "Fragment");

    // E, por fim, criamos o programa do shader, onde linkamos todos os outros shaders.
    // E verifica por erros, também!
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    CheckShader(shaderProgram, "Program");

    // Deletamos os shaders, já que não precisamos mais.
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

// Aqui onde o programa é deletado ao final da execução.
Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

// Método para usar o programa do Shader.
void Shader::UseProgram() {
    glUseProgram(shaderProgram);
}

// Coloca um valor inteiro à uma variável uniform do shader.
void Shader::SetIntUniform(const char* name, const int& value) {
    GLint location = glGetUniformLocation(shaderProgram, name);
    glUniform1i(location, value);
}

// Coloca um valor vec4 à uma variável uniform do shader.
void Shader::SetVec4Uniform(const char* name, const glm::vec4& value) {
    GLint location = glGetUniformLocation(shaderProgram, name);
    glUniform4fv(location, 1, glm::value_ptr(value));
}

// Método para pegar o programa do Shader.
GLuint Shader::GetProgram() {
    return shaderProgram;
}

// Verificação de erros do shader
void Shader::CheckShader(GLuint shader, const std::string& type) {
    // Verifica o tipo e mostra no terminal o erro.
    if (type == "Program") {
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cerr << "Shader Program não conseguiu linkar:\n" << infoLog << "\n";
        }
    } else {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            GLchar infolog[512];
            glGetShaderInfoLog(shader, 512, NULL, infolog);

            std::cerr << type << " shader não carregou: \n" << infolog << "\n";
        }
    }
}

// Método para ler os arquivos do shader e retornar uma string.
std::string Shader::ReadFile(const std::string path) {
    std::ifstream file(path);   // Abrindo o arquivo.

    // Se não abrir, mostrar que não foi possível abrir o arquivo e retornar vazio.
    if (!file.is_open()) {
        std::cerr << "Erro ao ler o arquivo: " << path << "\n";

        return "";
    }

    // Aqui, criamos um espaço na memória para colocar o conteúdo do arquivo.
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str(); // Depois, retornamos o conteúdo.
}