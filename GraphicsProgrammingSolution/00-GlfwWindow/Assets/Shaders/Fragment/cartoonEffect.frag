#version 450
layout(early_fragment_tests) in;

layout (std140) uniform LightBlock
{
	vec3 position;
	vec3 color;
}light;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec4 specular;
};

uniform Material material;

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec3 eyePosition;
}fs_in;

const int levels = 3;
const float scaleFactor = 1.0f / levels;

vec3 adsToon(vec3 position, vec3 normal)
{
	vec3 lightDir = normalize(light.position - position);
	float lDotN = max(0.0,dot(normal,lightDir));
	vec3 diffuse =  material.diffuse * floor(lDotN * levels) * scaleFactor;
	return light.color * (material.ambient  + diffuse);
}

out vec4 color;

void main()
{
	color = vec4(adsToon(fs_in.position, fs_in.normal),1.0f);
}