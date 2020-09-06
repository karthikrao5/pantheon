//
// Created by Karthik Rao on 9/6/20.
//

#ifndef PANTHEON_VERTEXBUFFER_H
#define PANTHEON_VERTEXBUFFER_H

class VertexBuffer {
private:
    unsigned int m_RendererID;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer(); //C++ destructor

    void bind() const;
    void unBind() const;
};
#endif //PANTHEON_VERTEXBUFFER_H
