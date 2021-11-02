//
// Created by ben on 02/11/2021.
//

#include "libs.h"
#include "runFrame.h"
#include "renderLoop.h"

void renderLoop(GLFWwindow *window, GLuint core_program, GLuint vao, unsigned int indicesCount) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        updateInput(window);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glUseProgram(core_program);

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
        runFrame();

        glfwSwapBuffers(window);
        glFlush();
        glBindVertexArray(0);
        glUseProgram(0);
    }
}

void updateInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}