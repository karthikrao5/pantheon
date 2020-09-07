//
// Created by Karthik Rao on 9/6/20.
//

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#ifndef PANTHEON_VERTEXARRAY_H
#define PANTHEON_VERTEXARRAY_H

class VertexArray{
private:
    unsigned int m_RendererID;
public:
    VertexArray();

    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind();
    void unBind();
};

#endif //PANTHEON_VERTEXARRAY_H
