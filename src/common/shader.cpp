//
// Created by Karthik Rao on 8/29/20.
//
#include "shader.h"
#include "utils.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <glad/glad.h>
#include <iostream>

unsigned int Shader::loadShader(const char *vertex_file_path, const char *fragment_file_path) {
    // Read the Vertex Shader code from the file
    std::string vsCode = readSource(vertex_file_path);

    // Read the Fragment Shader code from the file
    std::string fsCode = readSource(fragment_file_path);

    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vsCode);
    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fsCode);

    // Link the program

    unsigned int programId = glCreateProgram();

    GLCall(glAttachShader(programId, vertexShaderId))
    GLCall(glAttachShader(programId, fragmentShaderId))
    GLCall(glLinkProgram(programId))
    GLCall(glValidateProgram(programId))

    // Check the program
    GLCall(glGetProgramiv(programId, GL_LINK_STATUS, &result))
    GLCall(glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength))
    if (infoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(infoLogLength + 1);
        GLCall(glGetProgramInfoLog(programId, infoLogLength, nullptr, &ProgramErrorMessage[0]));
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    std::cout << "Shader successfully linked with id: " << programId << std::endl;

//    This deletes the shader source code, which is not good in case we use
//      Debugging tools
//    glDetachShader(programId, vertexShaderId);
//    glDetachShader(programId, fragmentShaderId);

    GLCall(glDeleteShader(vertexShaderId))
    GLCall(glDeleteShader(fragmentShaderId))

    return programId;
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source) {
    const char *src = source.c_str();
    unsigned int id = glCreateShader(type);
    GLCall(glShaderSource(id, 1, &src, nullptr))

    GLCall(glCompileShader(id))

    // Check Shader
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result))
    if (result == GL_FALSE) {
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength))
        char *shaderErrorMessage = (char *) alloca(infoLogLength * sizeof(char));
        GLCall(glGetShaderInfoLog(id, infoLogLength, &infoLogLength, shaderErrorMessage))
        printf("%s\n", &shaderErrorMessage[0]);
        GLCall(glDeleteShader(id))
        return 0;
    }

    return id;
}

std::string Shader::readSource(const char *file_path) {
    // Read the Shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(file_path, std::ios::in);
    if (shaderStream.is_open()) {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    } else {
        printf("Unable to open %s\n",
               file_path);
        getchar();
        return nullptr;
    }

    return shaderCode;
}

Shader::Shader(const char* vertex_filepath, const char* frag_filepath) {
    ProgramID = loadShader(vertex_filepath, frag_filepath);
}

Shader::~Shader() {
    GLCall(glDeleteShader(ProgramID))
}

void Shader::bind() const {
    GLCall(glUseProgram(ProgramID))
}

void Shader::unBind() {
    GLCall(glUseProgram(0))
}

void Shader::setUniformMat4f(const std::string& uniformName, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(getShaderLocation(uniformName), 1, GL_FALSE, &matrix[0][0]))
}

int Shader::getShaderLocation(const std::string& name) {
    if (m_LocationCache.find(name) != m_LocationCache.end()) {
        return m_LocationCache[name];
    }

    int location = glGetUniformLocation(ProgramID, name.c_str());
    if (location == -1) {
        std::cout << "Warning, uniform " << name << " does not exist!" << std::endl;
    }
    m_LocationCache[name] = location;

    return location;
}
