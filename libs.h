//
// Created by ben on 26/10/2021.
//

#ifndef GAME_ENGINE_LIBS_H
#define GAME_ENGINE_LIBS_H

#include <iostream>

#include <vector>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <SOIL2.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
};

#endif //GAME_ENGINE_LIBS_H
