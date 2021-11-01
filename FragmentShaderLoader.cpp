//
// Created by ben on 01/11/2021.
//

#include "libs.h"
#include "FragmentShaderLoader.h"

FragmentShaderLoader::FragmentShaderLoader(GLuint &program) {
    m_program = program;
}

void FragmentShaderLoader::load(const char *location) {
    std::string shader = ShaderLoader::fromFileSystem(location);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    char infoLog[512];
    GLint success;

    const GLchar *fragmentSrc = shader.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << std::endl << "ERROR: Could not compile fragment shader" << std::endl;
        std::cout << infoLog << std::endl;
        throw;
    }

    glAttachShader(m_program, fragmentShader);
    glDeleteShader(fragmentShader);

}
