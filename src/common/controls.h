//
// Created by Karthik Rao on 9/7/20.
//

#ifndef PANTHEON_CONTROLS_H
#define PANTHEON_CONTROLS_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Controls {
private:
    GLFWwindow *window;
    glm::vec3 cameraPos{};
    glm::vec3 cameraFront{};
    glm::vec3 cameraUp{};
    glm::vec3 direction{};

    float pitch;
    float yaw = -90.0f;

    float lastX = 640, lastY = 400;
    const float sensitivity = 0.1f;
    bool firstMouse = true;

    glm::mat4 view{};

    auto mouse_callback(GLFWwindow *window, double xpos, double ypos) -> void;

    inline static auto MouseCallback(GLFWwindow* window, double xpos, double ypos) -> void {
        auto * controls = static_cast<Controls *>(glfwGetWindowUserPointer(window));
        controls->mouse_callback(window, xpos, ypos);
    }

public:
    Controls(GLFWwindow *window);

    void handleInput();

    glm::mat4 getViewMatrix() const;
};

#endif //PANTHEON_CONTROLS_H
