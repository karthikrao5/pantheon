//
// Created by Karthik Rao on 8/29/20.
//

#ifndef OPENGL_TUTORIAL_SHADER_H
#define OPENGL_TUTORIAL_SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
    unsigned int ProgramID{};

    unsigned int loadShader(const char *vertex_file_path, const char *fragment_file_path);
private:
    GLint result = GL_FALSE;
    int infoLogLength{};

    unsigned int compileShader(unsigned int type, const std::string &source);
    static std::string readSource(const char *file_path);
};

#endif //OPENGL_TUTORIAL_SHADER_H
