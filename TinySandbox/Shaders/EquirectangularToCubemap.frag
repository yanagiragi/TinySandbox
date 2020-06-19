#version 330 core
out vec4 FragColor;
in vec3 WorldPos;

uniform sampler2D u_equirectangularMap;

// actually invAtan = vec4(1/2pi, 1/pi)
// used for mapping (pitch, yaw) from ([-pi, pi], [-pi/2, pi/2]) to ([-0.5, 0.5], [-0.5, 0.5])
// e.g. take (0,0,1) gets (0.75, 0), which is the center of the right half of the image
const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{		
    vec2 uv = SampleSphericalMap(normalize(WorldPos));
    vec3 color = texture(u_equirectangularMap, uv).rgb;
    
    FragColor = vec4(color, 1.0);
}