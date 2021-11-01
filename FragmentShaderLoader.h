//
// Created by ben on 01/11/2021.
//

#ifndef GAME_ENGINE_FRAGMENTSHADERLOADER_H
#define GAME_ENGINE_FRAGMENTSHADERLOADER_H

#include "ShaderLoader.h"

class FragmentShaderLoader : ShaderLoader {
private:
    GLuint m_program;
public:
    explicit FragmentShaderLoader(GLuint
                                  &program);

    void load(const char *location) override;
};


#endif //GAME_ENGINE_FRAGMENTSHADERLOADER_H
