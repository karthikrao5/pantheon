#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "common/shader.h"
#include "common/utils.h"
#include "common/VertexBuffer.h"
#include "common/IndexBuffer.h"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    const unsigned int WIDTH = 1280;
    const unsigned int HEIGHT = 720;

    GLFWwindow *window;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Game window", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Unable to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
//    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSwapInterval(1);
//    ================================================================
    unsigned int vaoId, programId;
    unsigned int vertexBufferId, colorBufferId, indexBufferId;
    std::vector<float> vertices = {
            // front
            -0.5, -0.5, 0.5,
            0.5, -0.5, 0.5,
            0.5, 0.5, 0.5,
            -0.5, 0.5, 0.5,
            // back
            -0.5, -0.5, -0.5,
            0.5, -0.5, -0.5,
            0.5, 0.5, -0.5,
            -0.5, 0.5, -0.5
    };

    std::vector<unsigned short> indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    std::vector<float> colors = {
            // front colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            // back colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0
    };

    Shader shader;
    const std::string vertexFile = "src/common/vertex_shader.glsl";
    const std::string fragFile = "src/common/frag.glsl";
    programId = shader.loadShader(vertexFile.c_str(), fragFile.c_str());

    GLCall(glGenVertexArrays(1, &vaoId))
    GLCall(glBindVertexArray(vaoId))
    std::cout << "vao: " << vaoId << std::endl;

//    GLCall(glGenBuffers(1, &vertexBufferId))
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId))
//    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), &vertices[0], GL_STATIC_DRAW))
    VertexBuffer vb = VertexBuffer(&vertices[0], vertices.size() * 3 * sizeof(float));
    GLCall(glEnableVertexAttribArray(0))
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr))
    std::cout << "vertex vbo: " << vertexBufferId << std::endl;

//    GLCall(glGenBuffers(1, &colorBufferId))
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, colorBufferId))
//    GLCall(glBufferData(GL_ARRAY_BUFFER, colors.size() * 3 * sizeof(float), &colors[0], GL_STATIC_DRAW))
    VertexBuffer cb = VertexBuffer(&colors[0], colors.size() * 3 * sizeof(float));
    GLCall(glEnableVertexAttribArray(1))
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr))
    std::cout << "color vbo: " << colorBufferId << std::endl;

    IndexBuffer ib = IndexBuffer(&indices[0], indices.size());
//    GLCall(glGenBuffers(1, &indexBufferId))
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId))
//    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW))
    std::cout << "index vbo: " << indexBufferId << std::endl;

    GLCall(glBindVertexArray(0))
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))

    glm::mat4 proj = glm::ortho(-9.0f, 9.0f, -7.0f, 7.0f, 1.0f, -1.0f);

    // Enable depth test
    GLCall(glEnable(GL_DEPTH_TEST))
    GLCall(glEnable(GL_CULL_FACE))
    // Accept fragment if it closer to the camera than the former one
    GLCall(glDepthFunc(GL_LESS))

    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
        GLCall(glClearColor(0.1, 0.1, 0.1, 1.0)) // set color to red

        GLCall(glUseProgram(programId))

        GLCall(glBindVertexArray(vaoId))
//        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId))
        ib.bind();

        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr))

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    GLCall(glfwDestroyWindow(window))

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
