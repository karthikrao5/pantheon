//
// Created by Karthik Rao on 9/6/20.
//

#include <glad/glad.h>
#include <iostream>
#include "Triangle.h"
#include "common/utils.h"
#include "common/shader.h"

void Triangle::init() {
    vertices = {
            // front
            -0.5, -0.5, 0.5,
            0.5, -0.5, 0.5,
            0.5, 0.5, 0.5,
            -0.5, 0.5, 0.5,
            // back
            -0.5, -0.5, -0.5,
            0.5, -0.5, -0.5,
            0.5, 0.5, -0.5,
            -0.5, 0.5, -0.5
    };

    indices = {
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

    colors = {
            // front colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            // back colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0
    };

    Shader shader;
    const std::string vertexFile = "src/common/vertex_shader.glsl";
    const std::string fragFile = "src/common/frag.glsl";
    programId = shader.loadShader(vertexFile.c_str(), fragFile.c_str());

    GLCall(glGenVertexArrays(1, &vaoId))
    GLCall(glBindVertexArray(vaoId))
    std::cout << "vao: " << vaoId << std::endl;

    GLCall(glGenBuffers(1, &vertexBufferId))
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId))
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), &vertices[0], GL_STATIC_DRAW))
    GLCall(glEnableVertexAttribArray(0))
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr))
    std::cout << "vertex vbo: " << vertexBufferId << std::endl;

    GLCall(glGenBuffers(1, &colorBufferId))
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, colorBufferId))
    GLCall(glBufferData(GL_ARRAY_BUFFER, colors.size() * 3 * sizeof(float), &colors[0], GL_STATIC_DRAW))
    GLCall(glEnableVertexAttribArray(1))
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr))
    std::cout << "color vbo: " << colorBufferId << std::endl;

    GLCall(glGenBuffers(1, &indexBufferId))
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId))
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW))
    std::cout << "index vbo: " << indexBufferId << std::endl;

    GLCall(glBindVertexArray(0))
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}

void Triangle::render() {
    GLCall(glUseProgram(programId))

    GLCall(glBindVertexArray(vaoId))
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId))

    GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr))
}
