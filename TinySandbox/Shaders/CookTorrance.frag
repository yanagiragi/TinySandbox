#version 400

const float PI = 3.1415926535;

uniform vec3 u_CameraPos;

uniform sampler2D  u_albedo;
uniform float u_metallic;
uniform float u_roughness;
uniform float u_ao;
uniform vec3 u_tint;

uniform samplerCube u_irradianceMap;
uniform samplerCube u_prefilterMap;
uniform sampler2D   u_brdfLUT; 

in vec2 textureCoord;
in vec3 normal;

in vec3 objectPosition;
in vec3 viewPosition;
in vec3 worldPosition;
in vec3 viewDir;

uniform mat4 u_ViewMatrix;

#define MAX_SUPPORT_LIGHT 4
#define MAX_REFLECTION_LOD 4.0

#define LIGHT_TYPE_DIRECTIONAL 0
#define LIGHT_TYPE_POINT 1
#define LIGHT_TYPE_SPOTLIGHT 2

uniform vec3 u_lightColor[MAX_SUPPORT_LIGHT];
uniform float u_lightIntensity[MAX_SUPPORT_LIGHT];
uniform vec3 u_lightPosition[MAX_SUPPORT_LIGHT];
uniform int u_lightType[MAX_SUPPORT_LIGHT];
uniform vec4 u_lightAdditional[MAX_SUPPORT_LIGHT];

out vec4 outColor;

vec3 Lambertian (vec3 albedo) 
{
	return albedo / PI;
}

float CalculateAttenuation(vec3 P, vec3 L, int type, vec4 additionalData)
{
	if (type == LIGHT_TYPE_DIRECTIONAL){
		return 1.0;
	}
	else if(type == LIGHT_TYPE_POINT){
		float d = length(P - L);
		return 1.0 / (d * d);
	}
	else if(type == LIGHT_TYPE_SPOTLIGHT){
		return 0.0; // not implementated yet
	}
	else {
		return 0.0;
	}
}

float DistributionGGX (vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom    = a2;
    float denom  = (NdotH2 * (a2 - 1.0) + 1.0);
    denom        = PI * denom * denom;
	
    return nom / denom;
}

// k_direct = (alpha + 1) * (alpha + 1) / 8
// k_IBL    = alpha * alpha / 2
float GeometrySchlickGGX (float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;	

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return nom / denom;
}
 
float GeometrySmith (vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 FresnelSchlick (float cosTheta, vec3 F0)
{
	cosTheta = clamp(cosTheta, 0.0, 0.99);

	// F0: the surface reflection at zero incidence
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 CookTorrance (vec3 N, vec3 V, vec3 L, vec3 F, vec3 albedo, float roughness)
{
	vec3 H = normalize(L + V);
	
	float D = DistributionGGX(N, H, roughness);
	//    F is passed in
	float G = GeometrySmith(N, V, L, roughness);

    float NdotWi = max(dot(N, L), 0.0);
    float NdotWo = max(dot(N, V), 0.0);

    vec3 norminator = D * F * G;
    float denominator = (4.0 * NdotWi * NdotWo) + 0.001;   // 0.001 for prevent divide by zero

    vec3 specular = norminator / denominator;

    return specular;
}

vec3 BRDF(vec3 N, vec3 V, vec3 L, vec3 F0, vec3 albedo, float metallic, float roughness)
{
	vec3 H = normalize(L + V);
	float HdotV = max(dot(H, V), 0.0);
	vec3 F = FresnelSchlick(HdotV, F0);

    vec3 kS = F; // equal to Fresnel
	vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic; // only non-metals have diffuse lighting, else do linear blend on partly metal

	return kD * Lambertian(albedo) + CookTorrance(N, V, L, F, albedo, roughness);
}

vec3 FresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
	cosTheta = clamp(cosTheta, 0.0, 0.99);
	return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

mat4 rotationX( in float angle ) {
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

mat4 rotationY( in float angle ) {
	return mat4(	cos(angle),		0,		sin(angle),	0,
			 				0,		1.0,			 0,	0,
					-sin(angle),	0,		cos(angle),	0,
							0, 		0,				0,	1);
}

mat4 rotationZ( in float angle ) {
	return mat4(	cos(angle),		-sin(angle),	0,	0,
			 		sin(angle),		cos(angle),		0,	0,
							0,				0,		1,	0,
							0,				0,		0,	1);
}

vec3 CollectLo(vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness)
{
	vec3 Lo = vec3(0.0);
	vec3 L;

	for(int i = 0; i < MAX_SUPPORT_LIGHT; ++i){

		if (u_lightType[i] == LIGHT_TYPE_DIRECTIONAL) {
			L = normalize(u_lightAdditional[i].xyz);
		}
		else {
			L = normalize(u_lightPosition[i] - worldPosition);
		}

		vec3 lightColor = u_lightColor[i] * u_lightIntensity[i];
		float attenuation = CalculateAttenuation(worldPosition, u_lightPosition[i], u_lightType[i], u_lightAdditional[i]);
		vec3 radiance = lightColor * attenuation;

		float NdotL = max(dot(N, L), 0.0);

		// calculate Lo
		Lo += BRDF(N, V, L, F0, albedo, metallic, roughness) * radiance * NdotL;
	}

	return Lo;
}

void main()
{
	// gamma space -> linear space
	vec3 albedo = pow(texture(u_albedo, textureCoord).rgb, vec3(2.2)) * u_tint;
	float metallic = u_metallic;
	float roughness = u_roughness;
	float ao = u_ao;
	
	vec3 N = normalize(normal);
    vec3 V = normalize(u_CameraPos - worldPosition);    
	vec3 R = reflect(-V, N);

	// simple assumption:
	// most dielectric surfaces look visually correct with a constant F0 of 0.04
	vec3 F0 = vec3(0.04); 
	F0      = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);
		
	Lo = CollectLo(N, V, F0, albedo, metallic, roughness);

	vec3 F = FresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);

	// ambient with respect to irradiance map
	vec3 kS = F; 
	vec3 kD = 1.0 - kS;
	kD *= 1.0 - metallic;

	// diffuse irradiance from env map
	vec3 irradiance = texture(u_irradianceMap, N).rgb;
	vec3 diffuse    = irradiance * albedo;

	// specular irradiance from env map
	vec3 prefilteredColor = textureLod(u_prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;
	vec2 brdf  = texture(u_brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
	vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

	vec3 ambient = (kD * diffuse + specular) * ao;	
	vec3 color = (ambient + Lo);

	// HDR tonemapping
	color = color / (color + vec3(1.0));
	// gamma correct	
	color = pow(color, vec3(1.0/2.2)); 
	
    outColor = vec4(color, 1.0);
}