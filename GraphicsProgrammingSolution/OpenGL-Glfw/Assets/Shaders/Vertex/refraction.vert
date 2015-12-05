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


uniform mat4 world;
uniform bool drawSkyBox;

struct Material{
	float eta;
	float reflectionFactor;
};

uniform Material material;

out VS_OUT
{
	vec3 refractDir;
	vec3 reflectDir;
}vs_out;

void main()
{
	if(drawSkyBox)
	{
		vs_out.reflectDir = position;
	}
	else
	{
		vec3 worldPosition = vec3(world * vec4(position,1.0));
		vec3 worldNormal = vec3(world * vec4(normal,0.0));
		vec3 worldView = normalize(transform.eyePosition - worldPosition);
		vs_out.reflectDir = reflect(-worldView, worldNormal);
		vs_out.refractDir = refract(-worldView, worldNormal, material.eta);
	}
	gl_Position = transform.projection * transform.view * world * vec4(position,1.0);
}