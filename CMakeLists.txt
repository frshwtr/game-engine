cmake_minimum_required(VERSION 3.20)
project(game_engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(game_engine main.cpp libs.h ShaderLoader.h VertexShaderLoader.cpp VertexShaderLoader.h FragmentShaderLoader.cpp FragmentShaderLoader.h UnsupportedSource.cpp UnsupportedSource.h)
target_include_directories(game_engine PRIVATE /usr/include/GLFW /usr/include/GL /usr/include/glm /usr/include/SOIL2)
target_link_libraries(game_engine -lglfw -lGLEW -lGL /usr/lib/soil2/libsoil2.so)
