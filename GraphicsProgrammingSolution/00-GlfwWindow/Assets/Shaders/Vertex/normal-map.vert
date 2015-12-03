#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 biTangent;

layout (std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;

out VS_OUT
{
	mat3 toObjectLocal;
	vec3 position;
	vec3 normal;
	vec2 uv;
	vec3 tangent;
}vs_out;

uniform mat4 world;

void main()
{
	vec4 worldPosition = world * vec4(position,1.0);
	vs_out.position = worldPosition.xyz;
	vs_out.normal = normal;
	vs_out.uv = uv;

	mat3 toLocal = mat3(
	tangent.x, biTangent.x, normal.x,
	tangent.y, biTangent.y, normal.y,
	tangent.z, biTangent.z, normal.z
	);
	
	vs_out.toObjectLocal = toLocal;

	gl_Position = transform.projection * transform.view * worldPosition;
}