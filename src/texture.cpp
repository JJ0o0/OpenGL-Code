#include "texture.h"

#include <iostream>

// Construtor que cria a textura.
Texture::Texture(const char* filePath) {
    glGenTextures(1, &ID);  // Gerando a textura vazia.
    glBindTexture(GL_TEXTURE_2D, ID);   // Especificando o tipo de textura.

    // Aqui definimos parametros como: Wrap e Filter.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Variáveis que armazenaremos os dados da imagem.
    int width, height, nrChannels;

    // Essa linha muda muita coisa.
    // O OpenGL tem um sistema de coordenada diferente do STBI (a lib que carrega imagens).
    // Enquanto o OpenGL carrega as coordenadas do centro, o STBI pega as coordenadas a partir do canto superior esquerdo.
    // Isso faz com que a imagem fique invertidade verticalmente.
    // Então, essa linha "desinverte" a imagem.
    stbi_set_flip_vertically_on_load(true);

    // Aqui pegamos as informações da imagem e colocamos num ponteiro.
    unsigned char* data = stbi_load(
        filePath, // Caminho do arquivo.
        &width, &height, // IMPORTANTE BOTAR COMO REFERÊNCIA DO PONTEIRO!
        &nrChannels, // IMPORTANTE BOTAR COMO REFERÊNCIA DO PONTEIRO!
        0 // Quantos canais tem?
    );

    // Se não der nenhum erro com o carregamento do arquivo.
    if (data) {
        // Aqui, detectamos o formato da imagem.
        // Só irá ser detectado: R, RGB, RGBA.
        // Porque são os mais comuns hoje em dia.
        GLenum format = GL_RGB;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            // Se não tiver o previsto, ele vai dar erro.
            std::cerr << "Número de canais não suportado: " << nrChannels << "\n";
            stbi_image_free(data);
            return;
        }

        // Aqui geramos a textura com as informações que pegamos antes.
        glTexImage2D(
            GL_TEXTURE_2D,
            0, format,
            width, height,
            0, format,
            GL_UNSIGNED_BYTE,
            data
        );

        // Essa linha gera várias texturas pequenas.
        // Isso faz com que a textura não fique estranha caso o objeto seja muito pequeno.
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        // Retorna um erro falando que a textura não conseguiu carregar.
        std::cout << "Não foi possível carregar a textura: " << filePath << "\n"; 
    }

    // Descartamos as informações usadas da imagem, já que criamos a textura.
    stbi_image_free(data);
}

// Destroi a textura.
Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

// Dá uma index à textura para o Fragment Shader ler.
void Texture::Bind(int bind) const {
    glActiveTexture(GL_TEXTURE0 + bind);
    glBindTexture(GL_TEXTURE_2D, ID);
}

// Tira essa index.
void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}