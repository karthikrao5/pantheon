//
// Created by Karthik Rao on 9/13/20.
//

#ifndef PANTHEON_MESH_H
#define PANTHEON_MESH_H

#include <glm/glm.hpp>
#include <iostream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
public:
    // mesh data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

private:
    VertexArray va{};
    VertexBuffer vb;
    IndexBuffer ib;
};

#endif //PANTHEON_MESH_H
