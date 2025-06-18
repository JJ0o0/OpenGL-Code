#version 330 core // Versão do GLSL
out vec4 FragColor; // Cor final.
in vec2 TexCoord; // Importando as coordenadas da textura do vertex.

// Setando as variáveis das texturas.
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // Misturando as duas texturas em 50%
    FragColor = mix(texture(texture1, TexCoord), 
                    texture(texture2, TexCoord),
                    0.5    
                );
}