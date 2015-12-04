#version 450
layout(early_fragment_tests) in;

layout(std140) uniform FogBlock
{
	float minDist;
	float maxDist;
	vec3 color;
}fog;


in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec3 eyePosition;
}fs_in;

out vec4 color;

void main()
{
	float dist = length(fs_in.eyePosition - fs_in.position);
	float fogFactor = clamp((fog.maxDist-dist)/(fog.maxDist - fog.minDist),0.0f,1.0f);
	color = vec4(mix(fog.color, fs_in.normal,fogFactor),1.0f);
}