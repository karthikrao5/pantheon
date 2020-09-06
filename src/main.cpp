#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "common/shader.h"
#include "Triangle.h"
#include "common/utils.h"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    const unsigned int WIDTH = 1280;
    const unsigned int HEIGHT = 720;

    GLFWwindow *window;
    unsigned int programId;

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

    Triangle triangle;
    triangle.init();

    glm::mat4 proj = glm::ortho(-9.0f, 9.0f, -7.0f, 7.0f, 1.0f, -1.0f);

    // Enable depth test
    GLCall(glEnable(GL_DEPTH_TEST))
    GLCall(glEnable(GL_CULL_FACE))
    // Accept fragment if it closer to the camera than the former one
    GLCall(glDepthFunc(GL_LESS))

    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
        GLCall(glClearColor(0.1, 0.1, 0.1, 1.0)) // set color to red

        triangle.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    GLCall(glfwDestroyWindow(window))

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
