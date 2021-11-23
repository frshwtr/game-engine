#include "libs.h"
#include "ShaderLoaderFactory.h"
#include "runFrame.h"
#include "renderLoop.h"
#include "glRules.h"

Vertex vertices[] = {
        glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),
        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),

        glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f)
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

int main() {
    glfwInit();

    unsigned verticesCountStatic = sizeof(vertices) / sizeof(Vertex);

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    enableGLRules();


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

    int image_width = 0;
    int image_height = 0;

    unsigned char *image = SOIL_load_image("textures/ainsley.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

    GLuint texture0;

    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    } else {
        std::cout << "ERROR: could not load image" << std::endl;
        return 1;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    int image_width1 = 0;
    int image_height1 = 0;

    unsigned char *image1 = SOIL_load_image("textures/gordon.png", &image_width1, &image_height1, NULL,
                                            SOIL_LOAD_RGBA);

    GLuint texture1;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    if (image1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    } else {
        std::cout << "ERROR: could not load image" << std::endl;
        return 1;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image1);

    glm::mat4 ModelMatrix(1.f);
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(50.f), glm::vec3(1.0f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));

    glUseProgram(core_program);
    glUniformMatrix4fv(glGetUniformLocation(core_program, "model_matrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUseProgram(0);
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));

    unsigned int indicesCount = sizeof(indices) / sizeof(GLuint);
    renderLoop(window, core_program, vao, indicesCount, texture0, texture1, ModelMatrix);

    glfwTerminate();
    return 0;
}

