#version 400

uniform sampler2D u_albedo;
uniform vec3 u_tint;
uniform vec2 u_tiling;
uniform float u_alpha;
uniform float u_emission;

in vec3 _worldNormal;
in vec2 _texCoord;

out vec4 outColor;

void main()
{
	outColor = texture2D(u_albedo, _texCoord * u_tiling) * vec4(u_tint, 1.0) * u_emission;
	outColor.a = u_alpha;
}