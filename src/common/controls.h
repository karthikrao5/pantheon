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
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 view;
public:
    Controls(GLFWwindow *window);

    void handleInput() const;

    glm::mat4 getViewMatrix() const;
};

#endif //PANTHEON_CONTROLS_H
