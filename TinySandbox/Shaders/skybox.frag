#version 330 core

uniform samplerCube u_environmentMap;
uniform float u_lod;

in vec3 WorldPos;

out vec4 FragColor;

void main()
{		
    vec3 envColor = textureLod(u_environmentMap, WorldPos, u_lod).rgb;
    
    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 

    FragColor = vec4(envColor, 1.0);
}