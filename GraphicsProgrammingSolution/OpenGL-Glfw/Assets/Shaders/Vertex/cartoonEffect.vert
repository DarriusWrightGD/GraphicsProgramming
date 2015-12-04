#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;

uniform mat4 world;

out VS_OUT
{
	vec3 position;
	vec3 normal;
	vec3 eyePosition;
}vs_out;

void main()
{
	vec4 worldPosition = world * vec4(position,1.0f); 
	vs_out.normal = normal;
	vs_out.position = worldPosition.xyz;
	gl_Position = transform.projection * transform.view * worldPosition;
}