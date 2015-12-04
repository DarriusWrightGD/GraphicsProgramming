#version 450

layout (early_fragment_tests) in;
layout (binding = 0) uniform sampler2D moss;
layout (binding = 1) uniform sampler2D brick;


in VS_OUT
{
	vec2 uv;
}fs_in;

out vec4 color;

void main()
{
	vec4 brickColor = texture(brick,fs_in.uv);
	vec4 mossColor = texture(moss,fs_in.uv);
	color = mix(brickColor, mossColor,mossColor.a);
}