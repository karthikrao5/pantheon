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
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "common/controls.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
//    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init("#version 330");

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("src/resources/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    std::vector<float> vertices = {
            // front
            -0.5, -0.5, 0.5,    1.0, 0.0, 0.0,  0.0f, 0.0f,   // bottom left
            0.5, -0.5, 0.5,     0.0, 1.0, 0.0,  1.0f, 0.0f,   // bottom right
            0.5, 0.5, 0.5,      0.0, 0.0, 1.0,  1.0f, 1.0f,   // top right
            -0.5, 0.5, 0.5,     1.0, 1.0, 1.0,  0.0f, 1.0f    // top left `
            // back
            -0.5, -0.5, -0.5,   1.0, 0.0, 0.0,  0.0f, 0.0f,   // bottom left
            0.5, -0.5, -0.5,    0.0, 1.0, 0.0,  1.0f, 0.0f,   // bottom right
            0.5, 0.5, -0.5,     0.0, 0.0, 1.0,  1.0f, 1.0f,   // top right
            -0.5, 0.5, -0.5,    1.0, 1.0, 1.0,  0.0f, 1.0f    // top left
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

    const std::string vertexFile = "src/resources/shaders/vertex_shader.glsl";
    const std::string fragFile = "src/resources/shaders/frag.glsl";
    Shader shader(vertexFile.c_str(), fragFile.c_str());

    VertexArray va;

    VertexBuffer vb = VertexBuffer(&vertices[0], vertices.size() * 3 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(3); // vec3 for x,y,z vertex positions
    layout.push<float>(3); // vec3 for r,g,b color values per vertex
    layout.push<float>(2); // vec2 for uv textcoords
    va.addBuffer(vb, layout);

    IndexBuffer ib = IndexBuffer(&indices[0], indices.size());

    GLCall(glBindVertexArray(0))
    vb.unBind();
    ib.unBind();

    shader.bind();
//    glm::mat4 proj = glm::ortho(-4.5f, 4.5f, -3.5f, 3.5f, 1.0f, -1.0f);
//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f,0 ));
//    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
//    glm::mat4 view(1.0f);
//    glm::mat4 view = glm::lookAt(
//            glm::vec3(5,5,4), // Camera is at (4,3,3), in World Space
//            glm::vec3(0,0,0), // and looks at the origin
//            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//    );

    Renderer renderer;
    Controls controls(window);
    glm::vec3 model_position(0, 0, 0);
    glm::vec3 rotation_vec(1.0f, 1.0f, 1.0f);

    float rotationRadians = 0;
    bool wireframeMode = false, xRot = true, yRot = false, zRot = false;

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        renderer.clear();

        {
            ImGui::Checkbox("xRot", &xRot);
            ImGui::SameLine();
            ImGui::Checkbox("yRot", &yRot);
            ImGui::SameLine();
            ImGui::Checkbox("zRot", &zRot);
            ImGui::SameLine();
            ImGui::Checkbox("Wireframe", &wireframeMode);
            ImGui::SliderFloat3("Translation", &model_position.x, 0.0f, 1.0f);
            ImGui::SliderFloat("Rotation", &rotationRadians, 0.0f, 1000.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }

        renderer.setWireframeMode(wireframeMode);

//        shader.bind();

        controls.handleInput();

        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view = controls.getViewMatrix();
        glm::mat4 proj = controls.getProjectionMatrix();
//        view = glm::lookAt(
//                glm::vec3(camX, 0.0, camZ),
//                glm::vec3(0.0, 0.0, 0.0),
//                glm::vec3(0.0, 1.0, 0.0)
//        );

//        view = controls.getViewMatrix();
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotationRadians * 2.0f),
                                         glm::vec3(xRot ? 1.0f : 0, yRot ? 1.0f : 0, zRot ? 1.0f : 0));
        glm::mat4 model = rotation * glm::translate(glm::mat4(1.0f), model_position);

        shader.setUniformMat4f("u_mvp", proj * view * model);

        renderer.draw(va, ib, shader);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    GLCall(glfwDestroyWindow(window))

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
