//
// Created by ben on 01/11/2021.
//

#include "libs.h"
#include "ShaderLoader.h"
#include "VertexShaderLoader.h"

VertexShaderLoader::VertexShaderLoader(GLuint &program) {
    m_program = program;
}

void VertexShaderLoader::load(const char *location) {
    std::string shader = VertexShaderLoader::fromFileSystem(location);

    char infoLog[512];
    GLint success;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexSrc = shader.c_str();
    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << std::endl << "ERROR: Could not compile vertex shader" << std::endl;
        std::cout << infoLog << std::endl;
        throw;
    }

    glAttachShader(m_program, vertexShader);
    glDeleteShader(vertexShader);
}
