//
// Created by Karthik Rao on 9/6/20.
//

#include <glad/glad.h>
#include "IndexBuffer.h"
#include "utils.h"

IndexBuffer::IndexBuffer(const unsigned short* data, unsigned int count) : m_Count(count ) {
    ASSERT(sizeof(unsigned short) == sizeof(GLushort))

    GLCall(glGenBuffers(1, &m_RendererID))
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID))
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned short), data, GL_STATIC_DRAW))
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
} //C++ destructor

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID))
}

void IndexBuffer::unBind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}