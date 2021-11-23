//
// Created by ben on 02/11/2021.
//

#include "libs.h"
#include "runFrame.h"
#include "renderLoop.h"

void renderLoop(GLFWwindow *window, GLuint core_program, GLuint vao, unsigned int indicesCount, GLuint texture0,
                GLuint texture1, glm::mat4 &modelMatrix) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        updateInput(window);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glUseProgram(core_program);

        glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);
        glUniform1i(glGetUniformLocation(core_program, "texture1"), 1);


        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(1.0f, 0.f, 0.f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(10.f), glm::vec3(0.f, 1.f, 0.f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));


        glUniformMatrix4fv(glGetUniformLocation(core_program, "model_matrix"), 1, GL_FALSE,
                           glm::value_ptr(modelMatrix));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
        runFrame();

        glfwSwapBuffers(window);
        glFlush();
        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void updateInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}