#version 450
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (std140 ) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;

uniform mat4 world;
uniform bool drawSkyBox;
uniform float reflectFactor;

out VS_OUT
{
	vec3 reflectDir;
	vec2 uv;

}vs_out;

void main()
{
	vec4 worldPosition =  world *vec4(position,1.0f) ;
	vs_out.uv = uv;

	if(drawSkyBox)
	{
		vs_out.reflectDir = position;
	}
	else
	{
		vec3 worldNorm = vec3(world * vec4(normal,0.0f));
		vec3 worldView = normalize(transform.eyePosition - worldPosition.xyz);
		vs_out.reflectDir = reflect(-worldView,worldNorm);
	}

	gl_Position = transform.projection * transform.view  * world* vec4(position,1.0);
}