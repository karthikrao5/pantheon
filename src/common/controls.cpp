//
// Created by Karthik Rao on 9/7/20.
//

#include "controls.h"

Controls::Controls(GLFWwindow *windowInput) {
    window = windowInput;

    glfwSetWindowUserPointer(windowInput, this);

    glfwSetCursorPosCallback(windowInput, MouseCallback);
    glfwSetScrollCallback(windowInput, ScrollCallback);

    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    direction = glm::vec3(0.0f, 0.0f, 0.0f);
    view = glm::lookAt(
            cameraPos,
            cameraPos + cameraFront,
            cameraUp);

    proj = glm::perspective(glm::radians(zoom), 1280.0f/720.0f, 0.1f, 100.0f);
//    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

}


void Controls::handleInput() {
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Controls::getViewMatrix() const {
    return view;
}

glm::mat4 Controls::getProjectionMatrix() const {
    return proj;
}

auto Controls::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) -> void {
    zoom -= (float) yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
    proj = glm::perspective(glm::radians(zoom), 1280.0f / 720.0f, 0.1f, 100.0f);

}

auto Controls::mouse_callback(GLFWwindow *window, double xpos, double ypos) -> void {
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

//    check contraints
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
