#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;



layout (std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
}transform;

layout (std140) uniform LightBlock
{
	vec3 color;
	vec3 position;
}light;



uniform mat4 world;
uniform vec3 diffuse;

out VS_OUT
{
	vec3 color;
}vs_out;

void main()
{
	vec4 worldPosition = world * vec4(position, 1.0);
	vec3 lightDirection =  light.position - vec3(worldPosition);
	
	vs_out.color = diffuse * light.color * max(dot(lightDirection, normal),0.0);
	gl_Position =  transform.projection * transform.view * worldPosition;
}