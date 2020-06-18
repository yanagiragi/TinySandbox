#version 330 core

//uniform samplerCube u_environmentMap;
uniform sampler2D u_environmentMap;

in vec3 WorldPos;

out vec4 FragColor;

void main()
{		
    //vec3 envColor = texture(u_environmentMap, WorldPos).rgb;
    vec3 envColor = texture(u_environmentMap, WorldPos.xy).rgb;

    /*
    1. Skybox Material line 58
    2. Texture line 75
    */

    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 

    FragColor = vec4(envColor, 1.0);

    // FragColor = vec4(WorldPos, 1.0);
}