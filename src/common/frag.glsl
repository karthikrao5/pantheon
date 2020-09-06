#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;

out vec3 FragColor;

void main()
{
    FragColor = fragmentColor;
}