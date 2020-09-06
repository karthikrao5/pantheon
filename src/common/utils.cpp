//
// Created by Karthik Rao on 9/6/20.
//

#include <glad/glad.h>
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGL error] (in hex: " << std::hex << error << ") from " << function << " " << file << " "
                  << line << std::endl;
        return false;
    }
    return true;
}