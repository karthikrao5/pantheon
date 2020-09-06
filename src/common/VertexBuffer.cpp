//
// Created by Karthik Rao on 9/6/20.
//

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "utils.h"
#include "iostream"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_RendererID))
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID))
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
    std::cout << "vbo id: " << m_RendererID << std::endl;
}

VertexBuffer::~VertexBuffer() {
 GLCall(glDeleteBuffers(1, &m_RendererID));
} //C++ destructor

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID))
}

void VertexBuffer::unBind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
}