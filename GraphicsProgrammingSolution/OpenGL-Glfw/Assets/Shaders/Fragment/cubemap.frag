#version 450

layout (early_fragment_tests) in;
layout(binding = 0) uniform samplerCube cubeMap;

uniform bool drawSkyBox;
uniform float reflectFactor;

in VS_OUT
{
	vec3 reflectDir;
	vec2 uv;
}fs_in;

uniform vec3 materialColor;
out vec4 color;
void main()
{
	color = texture(cubeMap, fs_in.reflectDir);
	if(!drawSkyBox)
	{
		color = mix(vec4(materialColor,1.0f), color,reflectFactor);
	}
}