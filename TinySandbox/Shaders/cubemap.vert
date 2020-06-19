#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 WorldPos;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

void main()
{
    WorldPos = aPos;  
    gl_Position =  u_projectionMatrix * u_viewMatrix * vec4(WorldPos, 1.0);
}

