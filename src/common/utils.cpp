//
// Created by Karthik Rao on 9/6/20.
//

#include <glad/glad.h>
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void GLCheckError() {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL error] (in hex: " << std::hex << error << ")" << std::endl;
    }
}