//
// Created by ben on 02/11/2021.
//

#include "libs.h"
#include "createBuffers.h"

void createBuffers(GLuint &vao, GLuint &vbo, GLuint &ebo, Vertex (&vertices)[], GLuint (&indices)[]) {
    std::cout << "Loading Buffers... ";

    std::cout << "Vertex Buffers... ";
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices), vertices, GL_STATIC_DRAW);

    std::cout << "Vertex Arrays... ";
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    std::cout << "Element Buffers... ";
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&indices), &indices, GL_STATIC_DRAW);

    std::cout << "Attribute Pointers... ";
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, position));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, color));

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, texcoord));

    glBindVertexArray(0);

    glUseProgram(0);
}