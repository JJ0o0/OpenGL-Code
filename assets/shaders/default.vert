#version 330 core // Versão do GLSL
layout (location = 0) in vec3 aPos; // Pegando o X, Y, Z do vertice.
layout (location = 1) in vec2 aTexCoord; // Pegando as coordenadas da Textura.

// Criando variável e enviando ela para o Fragment Shader.
out vec2 TexCoord;

void main() {
    // Passando a posição do vertíce para o shader.
    gl_Position = vec4(aPos, 1.0);

    // Setando as coordenadas da textura para o Fragment Shader.
    TexCoord = aTexCoord;
}