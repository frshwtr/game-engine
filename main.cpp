#include "libs.h"

void framebuffer_resize_callback(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
    glViewport(0, 0, frameBufferWidth, frameBufferWidth);
}


bool loadVertexShaders(GLuint &program, const char *shaderLocation) {
    char infoLog[512];
    GLint success;

    std::string buffer = "";
    std::string src = "";

    std::ifstream in_file;

    std::cout << "Vertex shaders.. ";
    in_file.open(shaderLocation);
    if (in_file.is_open()) {
        while (std::getline(in_file, buffer)) {
            src += buffer + "\n";
        }
    } else {
        std::cout << std::endl << "ERROR: Could not load shaders" << shaderLocation << std::endl;
        in_file.close();
        return success;
    }

    in_file.close();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexSrc = src.c_str();
    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << std::endl << "ERROR: Could not compile vertex shader" << std::endl;
        std::cout << infoLog << std::endl;
        return success;
    }

    buffer = "";
    src = "";


    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);

    return success;
}

bool loadFragmentShaders(GLuint &program, const char *shaderLocation) {
    char infoLog[512];
    GLint success;

    std::string buffer = "";
    std::string src = "";

    std::ifstream in_file;

    std::cout << "Fragment shaders.. ";
    in_file.open(shaderLocation);
    if (in_file.is_open()) {
        while (std::getline(in_file, buffer)) {
            src += buffer + "\n";
        }
    } else {
        std::cout << std::endl << "ERROR: Could not load shaders" << shaderLocation << std::endl;
        in_file.close();
        return false;
    }

    in_file.close();

    GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar *fragmentSrc = src.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << std::endl << "ERROR: Could not compile fragment shader" << std::endl;
        std::cout << infoLog << std::endl;
        return success;
    }

    buffer = "";
    src = "";

    glAttachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return success;
}

void runFrame() {

}

int main() {
    glfwInit();

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Engine", NULL, NULL);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "Something went wrong lol" << std::endl;
        glfwTerminate();
        return 1;
    }

    GLuint core_program;
    char infoLog[512];
    GLint success;
    std::cout << "Loading Shaders... ";
    core_program = glCreateProgram();

    if (!loadVertexShaders(core_program, "shaders/vertex/vertex_core.glsl") &&
        !loadFragmentShaders(core_program, "shaders/fragment/fragment_core.glsl")) {
        glfwTerminate();
    };

    glLinkProgram(core_program);
    glGetProgramiv(core_program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(core_program, 512, NULL, infoLog);
        std::cout << std::endl << "ERROR: Could not link program" << std::endl;
        std::cout << infoLog << std::endl;
    }
    glUseProgram(0);
    glLinkProgram(core_program);
    std::cout << "Done!" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        runFrame();

        glfwSwapBuffers(window);
        glFlush();
    }

    glfwTerminate();
    return 0;
}