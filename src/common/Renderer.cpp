//
// Created by Karthik Rao on 9/6/20.
//

#include "Renderer.h"
#include "utils.h"

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.bind();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_SHORT, nullptr))
}

void Renderer::clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
}

Renderer::Renderer() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Enable depth test
    GLCall(glEnable(GL_DEPTH_TEST))
    GLCall(glEnable(GL_CULL_FACE))
    // Accept fragment if it closer to the camera than the former one
    GLCall(glDepthFunc(GL_LESS))
}

Renderer::~Renderer() = default;

void Renderer::setWireframeMode(bool wireframeMode) const {
    glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
}
