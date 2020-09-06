//
// Created by Karthik Rao on 9/6/20.
//

#include <glad/glad.h>
#include <iostream>
#include "Triangle.h"

void Triangle::init() {
    unsigned int vertexBufferId, indexBufferId;

    vertices = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
    };

    indices = {
            0, 1, 2,
            2, 3, 0
    };

    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    std::cout << "vao: " << vaoId << std::endl;

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    std::cout << "vertex vbo: " << vertexBufferId << std::endl;

    glEnableVertexAttribArray(0);

//    each vertex is 3 floats big
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    std::cout << "index vbo: " << indexBufferId << std::endl;
}

void Triangle::render() {
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
}
