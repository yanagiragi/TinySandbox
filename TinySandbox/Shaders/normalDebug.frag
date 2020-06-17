#version 330 core

in vec3 _worldNormal;

out vec4 FragColor;

void main()
{
    // FragColor = vec4(1.0, 1.0, 0.0f, 1.0f);
    FragColor = vec4(_worldNormal, 1.0f);
}