//
// Created by ben on 02/11/2021.
//

#include "libs.h"
#include "runFrame.h"
#include "renderLoop.h"

void renderLoop(GLFWwindow *window, GLuint core_program, GLuint vao, unsigned int indicesCount, GLuint texture0,
                GLuint texture1, glm::mat4 &modelMatrix, glm::mat4 &projectionMatrix, int &frameBufferWidth,
                int &frameBufferHeight) {


}

void updateInput(GLFWwindow *window, glm::vec3 &position, glm::vec3 &rotation) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position.z -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position.z += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position.x -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position.x += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        rotation.y -= 1.f;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        rotation.y += 1.f;
    }
}