#pragma once

#include <glad/glad.h>

#include "stb_image.h"

class Texture {
private:
    unsigned int ID;
public:
    Texture(const char* filePath);
    ~Texture();

    void Bind(int bind=0) const;
    void Unbind() const;
};