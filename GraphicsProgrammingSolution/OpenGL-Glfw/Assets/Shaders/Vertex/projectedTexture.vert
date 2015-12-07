#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;

out VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 uv;
	vec4 projTexCoord;
}vs_out;

uniform mat4 world;
uniform mat4 normalMatrix;
uniform mat4 projectorMatrix;

void main()
{
	vs_out.position = (transform.view * world * vec4(position, 1.0f)).xyz;
	vs_out.uv = uv;
	vs_out.normal = normalize(normalMatrix* vec4(normal,0.0f)).xyz;
	vs_out.projTexCoord = projectorMatrix * (world * vec4(position,1.0f));
	gl_Position = transform.projection *transform.view * world *  vec4(position,1.0f);
}