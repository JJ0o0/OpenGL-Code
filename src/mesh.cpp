#include "mesh.h"

// Aqui, criamos as nossas Arrays: VBO, EBO e VAO.
Mesh::Mesh(const float* vertices, size_t verticeSize, const unsigned int* indices, size_t indiceSize) {
    glGenVertexArrays(1, &VAO);     // Geramos a VAO (vazia)
    glGenBuffers(1, &VBO);         // Geramos o VBO (vazio)
    glGenBuffers(1, &EBO);         // Geramos o EBO (vazio)

    glBindVertexArray(VAO);             /* 
                                                A partir de agora, todas as configurações de vertices
                                                 vão para o VAO.
                                              */

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Aqui, definimos o que é o VBO
    glBufferData(                                      // Configuramos o VBO.
        GL_ARRAY_BUFFER, 
        verticeSize,
        vertices,
        GL_STATIC_DRAW
    );

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Aqui, definimos o que é o EBO.
    glBufferData(                                              // Configuramos o EBO.
        GL_ELEMENT_ARRAY_BUFFER, 
        indiceSize,
        indices,
        GL_STATIC_DRAW
    );

    // VBO de novo
    glVertexAttribPointer(                            // Passamos a configurações dos vértices.
        0, 3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(float), 
        (void*)0
    );

    glEnableVertexAttribArray(0); // Limpamos a Array de Atributos dos Vertices  atual.
    glBindVertexArray(0);         // Limpamos a Array de Vertices atual.
}

// É aqui onde o programa deleta tudo.
Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);  // Deletamos o VAO.
    glDeleteBuffers(1, &VBO);      // Deletamos o VBO.
    glDeleteBuffers(1, &EBO);      // Deletamos o EBO.
}

// Colocando o VAO para funcionar.
void Mesh::Bind() const {
    glBindVertexArray(VAO);
}

// Tirando o VAO, e limpando a Array.
void Mesh::Unbind() const {
    glBindVertexArray(0);
}

// Desenhamos os vertíces usando os índices registrados pelo EBO.
void Mesh::Draw() const {
    Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    Unbind();
}