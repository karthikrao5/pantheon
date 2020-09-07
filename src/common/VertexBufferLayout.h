//
// Created by Karthik Rao on 9/6/20.
//

#include "vector"
#include <glad/glad.h>

#ifndef PANTHEON_VERTEXBUFFERLAYOUT_H
#define PANTHEON_VERTEXBUFFERLAYOUT_H

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
//        ASSERT(false) //shouldn't get here otherwise error
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout() : m_Stride(0) {};

    ~VertexBufferLayout();

    template<typename T>
    void push(unsigned int count) {}

    template<>
    void push<float>(unsigned int count){
        m_Elements.push_back({GL_FLOAT, count, false});
        m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    void push<unsigned int>(unsigned int count){
        m_Elements.push_back({GL_UNSIGNED_INT, count, false});
        m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char>(unsigned int count){
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, false});
        m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> getElements() const& { return m_Elements; }
    inline unsigned int getStride() const { return m_Stride; }
};

#endif //PANTHEON_VERTEXBUFFERLAYOUT_H
