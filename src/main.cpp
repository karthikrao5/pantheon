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
#include "common/VertexArray.h"
#include "common/Renderer.h"

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
    unsigned int programId;

    std::vector<float> vertices = {
            // front
            -0.5, -0.5, 0.5, 1.0, 0.0, 0.0,
            0.5, -0.5, 0.5, 0.0, 1.0, 0.0,
            0.5, 0.5, 0.5, 0.0, 0.0, 1.0,
            -0.5, 0.5, 0.5, 1.0, 1.0, 1.0,
            // back
            -0.5, -0.5, -0.5, 1.0, 0.0, 0.0,
            0.5, -0.5, -0.5, 0.0, 1.0, 0.0,
            0.5, 0.5, -0.5, 0.0, 0.0, 1.0,
            -0.5, 0.5, -0.5, 1.0, 1.0, 1.0
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

    const std::string vertexFile = "src/common/vertex_shader.glsl";
    const std::string fragFile = "src/common/frag.glsl";
    Shader shader(vertexFile.c_str(), fragFile.c_str());

    VertexArray va;

    VertexBuffer vb = VertexBuffer(&vertices[0], vertices.size() * 3 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(3); // vec3 for x,y,z vertex positions
    layout.push<float>(3); // vec3 for r,g,b color values per vertex
    va.addBuffer(vb, layout);

    IndexBuffer ib = IndexBuffer(&indices[0], indices.size());

    GLCall(glBindVertexArray(0))
    vb.unBind();
    ib.unBind();

    shader.bind();
    glm::mat4 proj = glm::ortho(-4.5f, 4.5f, -3.5f, 3.5f, 1.0f, -1.0f);
    shader.setUniformMat4f("u_mvp", proj);

    Renderer renderer;
    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        renderer.draw(va, ib, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    GLCall(glfwDestroyWindow(window))

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
