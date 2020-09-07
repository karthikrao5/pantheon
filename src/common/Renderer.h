//
// Created by Karthik Rao on 9/6/20.
//

#ifndef PANTHEON_RENDERER_H
#define PANTHEON_RENDERER_H

#include "VertexArray.h"
#include "shader.h"
#include "IndexBuffer.h"

class Renderer {
public:
    Renderer();

    ~Renderer();

    void clear() const;

    void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};

#endif //PANTHEON_RENDERER_H