#version 450

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 uv;

layout(std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
}transform;

out VS_OUT
{
	vec3 position;
	vec2 uv;
}vs_out;

uniform mat4 world;

void main()
{
	vec4 worldPosition = world * vec4(position,1.0f);
	vs_out.position = worldPosition.xyz;
	vs_out.uv = uv;
	gl_Position = transform.projection * transform.view * worldPosition;
}