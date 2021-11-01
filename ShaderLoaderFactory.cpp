//
// Created by ben on 01/11/2021.
//

#include <iostream>
#include "libs.h"
#include "ShaderLoaderFactory.h"
#include "FragmentShaderLoader.h"
#include "VertexShaderLoader.h"
#include "UnsupportedSource.h"

std::string extensionDelimeter = ".";
std::string extensionGLSL = "glsl";
std::string extensionFrag = "frag";
std::string extensionVert = "vert";

ShaderLoaderFactory::ShaderLoaderFactory(GLuint &program) {
    m_program = program;
}

void ShaderLoaderFactory::loadShaders(const std::list<const char *> &shaderSources) {
    std::list<std::exception> errors;
    for (auto it = shaderSources.cbegin(); it != shaderSources.cend(); it++) {
        std::cout << "Loading shaders from source: " << *it << std::endl;
        try {
            this->createShaderLoader(*it);
        } catch (std::exception e) {
            errors.push_back(e);
        }
    }
    if (!errors.empty()) throw;

}

void ShaderLoaderFactory::createShaderLoader(const char *shaderSource) {
    std::string source = shaderSource;
    std::string extension = source.substr(source.find_last_of(extensionDelimeter) + 1, source.length());

    if (extension == extensionFrag) {
        FragmentShaderLoader(m_program).load(shaderSource);
    } else if (extension == extensionVert) {
        VertexShaderLoader(m_program).load(shaderSource);
    } else if (extension == extensionGLSL) {
        std::cout << "ERROR: GLSL extension is not supported: " << shaderSource << std::endl;
        throw UnsupportedSource("GLSL extension is not supported");
    }
}
