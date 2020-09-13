#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}