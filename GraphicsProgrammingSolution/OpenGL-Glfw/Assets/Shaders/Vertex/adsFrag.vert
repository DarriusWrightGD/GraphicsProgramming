#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 uv;

layout(std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;


out VS_OUT
{
	vec3 normal;
	vec3 position;
	vec3 eyePosition;
}vs_out;

uniform mat4 world;
uniform mat4 normalMatrix;

void main()
{	
	vec4 worldPosition =transform.view * world * vec4(position,1.0f);
	vs_out.position = worldPosition.xyz;
	vs_out.normal = normalize(normalMatrix* vec4(normal,0.0f)).xyz;
	vs_out.eyePosition = transform.eyePosition;
	gl_Position = transform.projection * worldPosition;
}