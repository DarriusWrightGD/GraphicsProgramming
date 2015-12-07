#version 450
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 uv;


layout (std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
}transform;

uniform mat4 world;

out VS_OUT
{
	vec2 uv;
}vs_out;

void main()
{
	vs_out.uv = uv;
	gl_Position = transform.projection * transform.view * world  * vec4(position,1.0f);
}