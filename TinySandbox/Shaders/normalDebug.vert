#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 _worldNormal;

void main()
{
    mat4 normalMatrix = transpose(inverse(u_ModelMatrix));
	_worldNormal = normalize((normalMatrix * vec4(a_Normal, 1)).xyz); // this is correct , don't use raw normal or MV * normal

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}