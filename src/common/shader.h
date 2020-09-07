//
// Created by Karthik Rao on 8/29/20.
//

#ifndef OPENGL_TUTORIAL_SHADER_H
#define OPENGL_TUTORIAL_SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader {
public:
    unsigned int ProgramID{};
    std::unordered_map<std::string, int> m_LocationCache;

    Shader(const char *vertex_filepath, const char *frag_filepath);
    ~Shader();

    void bind() const;
    static void unBind();

    unsigned int loadShader(const char *vertex_file_path, const char *fragment_file_path);
    void setUniformMat4f(const std::string& uniformName, const glm::mat4& matrix);
private:
    GLint result = GL_FALSE;
    int infoLogLength{};

    unsigned int compileShader(unsigned int type, const std::string &source);
    static std::string readSource(const char *file_path);

    int getShaderLocation(const std::string& name);
};

#endif //OPENGL_TUTORIAL_SHADER_H
