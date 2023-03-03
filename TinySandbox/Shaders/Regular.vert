#version 400

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextureCoord;
// layout(location = 3) in vec3 aTangent;
// layout(location = 4) in vec3 aBitangent;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform vec3 u_CameraPos;

out vec3 objectPosition;
out vec3 viewPosition;
out vec3 worldPosition;
out vec2 textureCoord;

out vec3 normal;
/*out mat3 TBN;
out vec3 tangent;
out vec3 bitangent;*/

void main() {
    objectPosition = aPosition;
    textureCoord = aTextureCoord;
    
    mat4 ModelViewMatrix = u_ViewMatrix * u_ModelMatrix;

    viewPosition = vec3(ModelViewMatrix *  vec4(aPosition , 1.0));
    worldPosition = vec3(u_ModelMatrix * vec4(aPosition, 1.0));
    
    // Consider Compute it in CPU then send in with uniform
    mat4 normalMatrix = transpose(inverse(u_ModelMatrix));
    normal = normalize((normalMatrix * vec4(aNormal, 1)).xyz); // this is correct , don't use raw normal or MV * normal
        
    /*vec3 T = normalize(vec3(normalMatrix * vec4(aTangent,   0.0)));
    vec3 B = normalize(vec3(normalMatrix * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(normalMatrix * vec4(aNormal,    0.0)));
    TBN = mat3(T, B, N);

    tangent = T;
    bitangent = B;*/

    gl_Position = u_ProjectionMatrix * ModelViewMatrix * vec4(aPosition , 1.0);
}