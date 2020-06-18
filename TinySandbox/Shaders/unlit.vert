#version 400

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextureCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 normal;

out vec2 textureCoord;

void main() {
	normal = aNormal;
	textureCoord = aTextureCoord;
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix *  vec4(aPosition , 1.0);
}