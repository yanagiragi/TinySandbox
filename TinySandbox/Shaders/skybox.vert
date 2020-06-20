#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec3 _worldPos;

void main()
{
    _worldPos = aPos;

	mat4 rotView = mat4(mat3(u_ViewMatrix));
	vec4 clipPos = u_ProjectionMatrix * rotView * vec4(_worldPos, 1.0);

	gl_Position = clipPos.xyww;
}

