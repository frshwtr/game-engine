//
// Created by ben on 02/11/2021.
//

#ifndef GAME_ENGINE_RENDERLOOP_H
#define GAME_ENGINE_RENDERLOOP_H

void renderLoop(GLFWwindow *window, GLuint core_program, GLuint vao, unsigned int indicesCount, GLuint &texture);

void updateInput(GLFWwindow *window);


#endif //GAME_ENGINE_RENDERLOOP_H
