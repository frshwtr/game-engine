//
// Created by ben on 01/11/2021.
//

#ifndef GAME_ENGINE_VERTEXSHADERLOADER_H
#define GAME_ENGINE_VERTEXSHADERLOADER_H

#include "libs.h"
#include "ShaderLoader.h"

class VertexShaderLoader : ShaderLoader {
private:
    GLuint m_program;
public:
    explicit VertexShaderLoader(GLuint &program);

    void load(const char *location) override;
};

#endif //GAME_ENGINE_VERTEXSHADERLOADER_H

