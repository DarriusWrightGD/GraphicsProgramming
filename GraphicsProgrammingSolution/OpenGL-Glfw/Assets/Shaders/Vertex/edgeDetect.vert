#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout (std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
}transform;

uniform mat4 world;

void main()
{
	gl_Position = transform.projection * transform.view * world * vec4(position,1.0f);
}