
#include <gl.h>
#include <list>

#//
// Created by ben on 01/11/2021.
//

#ifndef GAME_ENGINE_SHADERFACTORY_H
#define GAME_ENGINE_SHADERFACTORY_H


class ShaderLoaderFactory {
private:
    GLuint m_program;

    void createShaderLoader(const char *shaderSource);

public:
    explicit ShaderLoaderFactory(GLuint &program);

    void loadShaders(const std::list<const char *> &shaderSources);
};


#endif //GAME_ENGINE_SHADERFACTORY_H
