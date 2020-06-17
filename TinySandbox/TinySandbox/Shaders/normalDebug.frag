#version 330 core

uniform float time;

out vec4 FragColor;

void main()
{
    FragColor = vec4(sin(time) / 2.0 + 0.5f, 0.5f, 0.2f, 1.0f);
}