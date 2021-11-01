#include "libs.h"
#include "ShaderLoaderFactory.h"

Vertex vertices[] = {
        glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),
        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),

        glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f)
};


//TODO: make this work, doesn't like the input for some reason
unsigned verticesSizeof(Vertex verticesArr[]) {
    return sizeof(verticesArr) / sizeof(Vertex);
}

GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
};

unsigned indicesSizeof(GLuint indicesArr[]) {
    return sizeof(indicesArr) / sizeof(GLuint);
}

void initialiseBuffers(GLuint &vao, GLuint &vbo, GLuint &ebo);

void framebuffer_resize_callback(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

void updateInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void runFrame() {

}

int main() {
    glfwInit();

    unsigned verticesCountStatic = sizeof(vertices) / sizeof(Vertex);

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
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

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLuint core_program;
    char infoLog[512];
    GLint success;
    core_program = glCreateProgram();

    ShaderLoaderFactory shaderLoader(core_program);

    try {
        shaderLoader.loadShaders({"shaders/vertex/vertex_core.vert", "shaders/fragment/fragment_core.frag"});
    } catch (std::exception _e) {
        std::cout << "Error whilst loading core shaders..";
        glfwTerminate();
        return 1;
    }

    std::cout << "Done!" << std::endl;


    std::cout << "Linking program... ";
    glLinkProgram(core_program);
    glGetProgramiv(core_program, GL_LINK_STATUS, &success);


    if (!success) {
        glGetProgramInfoLog(core_program, 512, NULL, infoLog);
        std::cout << std::endl << "ERROR: Could not link program" << std::endl;
        std::cout << infoLog << std::endl;
        return 1;
    }

    glUseProgram(0);
    std::cout << "Done!" << std::endl;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    std::cout << "Loading Buffers... ";

    std::cout << "Vertex Buffers... ";
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    std::cout << "Vertex Arrays... ";
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    std::cout << "Element Buffers... ";
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    std::cout << "Attribute Pointers... ";
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, position));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, color));

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, texcoord));

    glBindVertexArray(0);

    glUseProgram(0);

    std::cout << "Done!" << std::endl;

    std::cout << "Ready to render!" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        updateInput(window);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glUseProgram(core_program);

        glBindVertexArray(vao);
        unsigned int indicesCount = sizeof(indices) / sizeof(GLuint);
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
        runFrame();

        glfwSwapBuffers(window);
        glFlush();
        glBindVertexArray(0);
        glUseProgram(0);
    }

    glfwTerminate();
    return 0;
}
