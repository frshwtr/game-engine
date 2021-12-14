//
// Created by ben on 02/11/2021.
//

#ifndef GAME_ENGINE_RENDERLOOP_H
#define GAME_ENGINE_RENDERLOOP_H

void renderLoop(GLFWwindow *window, GLuint core_program, GLuint vao, unsigned int indicesCount, GLuint texture0,
                GLuint texture1, glm::mat4 &modelMatrix, glm::mat4 &projectionMatrix, int &frameBufferWidth,
                int &frameBufferHeight);

void updateInput(GLFWwindow *window, glm::vec3 &position, glm::vec3 &rotation);


#endif //GAME_ENGINE_RENDERLOOP_H
