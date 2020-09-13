#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 aTexCoord;

// Values that stay constant for the whole mesh.
uniform mat4 u_mvp;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
out vec2 TexCoord;

void main()
{
    gl_Position = u_mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
//
//    // The color of each vertex will be interpolated
//    // to produce the color of each fragment
    fragmentColor = vertexColor;
    TexCoord = aTexCoord;
}